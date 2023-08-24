#include "ClMovementLearner.hpp"


ClMovementLearner::~ClMovementLearner(){}


int ClMovementLearner::Create(std::shared_ptr<ClMovementLearner>& po_new_instance)
{
    po_new_instance = std::make_shared<ClMovementLearner>();
    return 1;    
}

int ClMovementLearner::ComputeMovements(std::vector<float>& p_previous_timestep_variables, std::vector<ClMovement>& p_previous_timestep_variables_movements, std::vector<float>& p_next_timestep_variables, std::vector<ClMovement>& po_new_transition_movements)
{
    if(p_previous_timestep_variables.size()==0 || p_next_timestep_variables.size()==0)
    {
        return -1;
    }

    if(p_next_timestep_variables.size() != p_previous_timestep_variables_movements.size())
    {
        return -3;
    }

    po_new_transition_movements = std::vector<ClMovement>(p_previous_timestep_variables_movements.size());

    for(std::size_t variable_index=0; variable_index<p_previous_timestep_variables.size(); variable_index++)
    {
        float point1 = p_previous_timestep_variables[variable_index];
        float point2 = p_next_timestep_variables[variable_index];

        float new_velocity = (point2 - point1) / 1.0;  // Assuming time step is 1.0
        po_new_transition_movements[variable_index].m_velocity = new_velocity;

  
        /*
        *    Compute new acceleration
        */
        float acceleration_previous_timestep_velocity = 0.00;

        if(p_previous_timestep_variables_movements.size() != 0)
        {
            acceleration_previous_timestep_velocity = p_previous_timestep_variables_movements[variable_index].m_velocity;
        }

        float new_acceleration = (new_velocity - acceleration_previous_timestep_velocity) / 1.0;  // Assuming time step is 1.0                
        po_new_transition_movements[variable_index].m_acceleration = new_acceleration;
    }

    return 1; 
}

int ClMovementLearner::AddTimestep(std::vector<float>& p_current_timestep_variables, std::shared_ptr<void>& po_new_transition_data)
{
    /*
    *    We will create the instance, not the user
    */
    if(po_new_transition_data != nullptr)
    {
        return -1;
    }

    if(p_current_timestep_variables.size()==0)
    {
        return -2;
    }

    std::shared_ptr<std::vector<ClMovement>> po_new_movements = std::make_shared<std::vector<ClMovement>>(p_current_timestep_variables.size());

    if(this->m_previous_timestep_variables.size()==0)
    {
        this->m_previous_timestep_variables = p_current_timestep_variables;
        this->m_previous_timestep_movements = *po_new_movements;
        po_new_transition_data = po_new_movements;
        return 1;
    }

    if(this->m_previous_timestep_variables.size() != p_current_timestep_variables.size())
    {
        return -3;
    }

    if(p_current_timestep_variables.size() != this->m_previous_timestep_movements.size())
    {
        return -6;
    }


    std::vector<ClMovement> new_movements;
    int result = this->ComputeMovements(this->m_previous_timestep_variables, this->m_previous_timestep_movements, p_current_timestep_variables, new_movements);
    if(result != 1)
    {
        return -7;
    }

    *po_new_movements = new_movements;
    po_new_transition_data = po_new_movements;

    return 1;
}


void ClMovementLearner::Print(std::shared_ptr<void> p_transition_data)
{
    std::cout << "==== Printing [ClMovementLearner] movements ====" << std::endl;
    std::shared_ptr<std::vector<ClMovement>> movements = std::static_pointer_cast<std::vector<ClMovement>>(p_transition_data);

    for (std::size_t i=0; i<movements->size(); i++) 
    {
        std::cout << "[" << i << "] : [Velocity :" << movements->at(i).m_velocity << "], [Acceleration : " << movements->at(i).m_acceleration << "]"  << std::endl;
    }
    std::cout << std::endl << "==== End of [ClMovementLearner] movements ====" << std::endl;      
}

// int ClMovementLearner::Predict(STATE_CHAIN_POINTER p_state_chain, float& po_predicted_value);
// int ClMovementLearner::Learn(STATE_CHAIN_POINTER p_state_chain, float p_predicted_value, float p_actual_value);