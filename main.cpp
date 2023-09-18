#include "Include/ClState.hpp"
#include "Include/ClStateChain.hpp"
#include "Include/ProblemSolving/ClOperator.hpp"
#include "Include/ProblemSolving/ClProblem.hpp"



#include "Include/Learners/Movement/ClMovementLearner.hpp"
#include "Include/StateReaders/Memcache/ClMemcacheStateReader.hpp"


#include <string>
#include <sstream>
#include <iostream>

STATE_POINTER g_initial_state = nullptr;
STATE_CHAIN_POINTER g_states_chain = nullptr;

const std::size_t g_number_of_variables_per_state = 1;


int operator_wait(STATE_POINTER& p_source_state, STATE_POINTER& po_destination_pointer)
{
    return 1;
}


int main()
{
    std::cout << "Initializing...please wait" << std::endl;

    int result = 0;

    result = ClStateChain::Create(g_states_chain);
    if(result != 1)
    {
        std::cout << "Error running [ClStateChain::Create] with result [" << result << "]" << std::endl;
        return -1;
    }


    /*
    *    Instanciate our state reader
    */
    MEMCACHE_STATE_READER_POINTER memcache_state_reader = nullptr;
    result = ClMemcacheStateReader::Create(memcache_state_reader);
    if(result != 1)
    {
        std::cout << "Error running [ClMemcacheStateReader::Create] with result [" << result << "]" << std::endl;
        return -1;
    }    


    /*
    *    Instanciate our learners
    */
    MOVEMENT_LEARNER_POINTER movement_learner = nullptr;
    result = ClMovementLearner::Create(movement_learner);
    if(result != 1)
    {
        std::cout << "Error running [ClMovementLearner::Create] with result [" << result << "]" << std::endl;
        return -2;        
    }

    g_states_chain->m_learner_instances.push_back(movement_learner);


    


    std::cout << "Populating initial state..." << std::endl;

    while(1)
    {
        STATE_POINTER new_timestep_state = nullptr;
        
        std::cout << "Waiting for new timestep" << std::endl;
        result = memcache_state_reader->WaitForNewState(new_timestep_state);
        if(result != 1)
        {
            std::cout << "Error running [ClMemcacheStateReader::WaitForNewState] with result [" << result << "]" << std::endl;
            return -3;                    
        }
        std::cout << "New timestep arrived" << std::endl;

        g_states_chain->AddState(new_timestep_state);


        /*
        *   What do we predict for the next state ?
        *   If we notice that letting thing run their course wont get us closer to our goal, 
        *   we can intervene and apply an operator to the current state.
        */


        float predicted_position;
        if(g_states_chain->m_blocks.back().m_predictive_next_state != nullptr)
        {
            predicted_position = g_states_chain->m_blocks.back().m_predictive_next_state->m_state_variables.back();
        }

        std::cout << "Current ball position [" << new_timestep_state->m_state_variables.back() << "],  predicted next position [" << predicted_position << "]" << std::endl;

        // std::cout << "Latest block of global state chain for timestep [" << g_current_timestep << "]" << std::endl;
        // g_states_chain->Print();
        // std::cout << "Press any key to keep running" << std::endl;
        // std::cout << "==================================================" << std::endl;

        // std::cout << std::endl << std::endl << std::endl;

        // std::string rien;
        // std::cin >> rien;
    }





    

    return 0;
}


//step 1 : make a model of the world through association , then intervention, then conterfactuals
//step 2 : defined the ultimate goal
//step 3 : sub/problem solving loop


