
#include "ClMemcacheStateReader.hpp"


ClMemcacheStateReader::ClMemcacheStateReader(){}
ClMemcacheStateReader::~ClMemcacheStateReader(){}

int ClMemcacheStateReader::Create(std::shared_ptr<ClMemcacheStateReader>& po_new_instance)
{
    po_new_instance = std::make_shared<ClMemcacheStateReader>();
    if(po_new_instance->Initialize()!=1)
    {
        return -1;
    }

    return 1;        
}

int ClMemcacheStateReader::Initialize()
{
    this->m_memcache_handle = memcached_create(NULL);
    this->m_memcache_server_list = memcached_server_list_append(NULL, "memcache_server", 11211, nullptr);
    memcached_return_t rc = memcached_server_push(this->m_memcache_handle, this->m_memcache_server_list);

    if (rc != MEMCACHED_SUCCESS) 
    {
        //std::cerr << "Memcached connection failed: " << memcached_strerror(memc, rc) << std::endl;
        return -1;
    }    


    std::cout << "Successfully connect to memcache" << std::endl;
    this->m_last_processed_timestep = 0;

    return 1;
}

int ClMemcacheStateReader::WaitForNewState(std::shared_ptr<ClState>& po_new_state)
{


    /*
    *    Fetch the [timestep] variable from memcache
    */
    const std::string timestep_key("timestep");   
    memcached_return_t rc;

    while(1)
    {
        char* timestep_str = nullptr;
        std::size_t timestep = 0;
        size_t timestep_length = 0;

        timestep_str = memcached_get(this->m_memcache_handle, timestep_key.c_str(), timestep_key.length(), &timestep_length, nullptr, &rc);

        if (rc != MEMCACHED_SUCCESS) 
        {
            //std::cerr << "Failed to retrieve timestep from Memcached: " << memcached_strerror(this->m_memcache_handle, rc) << std::endl;
            continue;
            //return -1;
        }

        // Convert timestep to std::size_t
        if (sscanf(timestep_str, "%zu", &timestep) != 1) 
        {
            std::cerr << "Failed to convert timestep to std::size_t." << std::endl;
            free(timestep_str);  // Free the allocated memory
            return -2;
        }

        free(timestep_str);  // Free the allocated memory




        /*
        *    Is our timestep valid ?
        */
        if(timestep > this->m_last_processed_timestep)
        {
            std::cout << "yes, received timestep [" << timestep << "] from memcache" << std::endl;
            this->m_last_processed_timestep = timestep;
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    

    /*
    *    Fetch the [variable_values] from memcache, needed to create our new [ClState]
    */
    const std::string variable_values_key("variable_values");
    char* value_str;
    size_t value_length;

    value_str = memcached_get(this->m_memcache_handle, variable_values_key.c_str(), variable_values_key.length(), &value_length, nullptr, &rc);

    if (rc != MEMCACHED_SUCCESS) 
    {
        std::cerr << "Failed to retrieve [variable_values] from Memcached: " << memcached_strerror(this->m_memcache_handle, rc) << std::endl;
        return -3;
    }

    // Convert variable_values to a vector of floats
    std::vector<float> variable_values;
    std::string variable_values_str(value_str, value_length);
    //std::cout << variable_values_str << std::endl;
    std::stringstream iss(variable_values_str);
    float value;
    variable_values.clear();  // Clear the vector to ensure it's empty

    while (iss >> value) 
    {
        variable_values.push_back(value);
    }

    free(value_str);  // Free the allocated memory




    /*
    *    Awesome, now we can create our new state instance, and populate it using the content of [variable_values]
    */
    std::shared_ptr<ClState> new_state = nullptr;
    if(ClState::Create(variable_values.size(),new_state) != 1)
    {
        return -4;
    }

    new_state->m_state_variables = variable_values;
    po_new_state = new_state;

    return 1;    
}


int ClMemcacheStateReader::Uninitialize()
{
    memcached_server_list_free(this->m_memcache_server_list);
    memcached_free(this->m_memcache_handle);

    return 1;
}