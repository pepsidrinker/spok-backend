#include "ClMovementLearner.hpp"



int ClMovementLearner::ComputeMovements(STATE_POINTER p_previous_timestep_state, std::shared_ptr<std::vector<ClMovement>>& p_previous_timestep_state_movements, STATE_POINTER p_next_timestep_state, std::shared_ptr<std::vector<ClMovement>>& po_new_transition_movements)
{
    if(p_previous_timestep_state == nullptr || p_next_timestep_state == nullptr)
    {
        return -1;
    }

    if(p_previous_timestep_state->m_state_variables.size() != p_next_timestep_state->m_state_variables.size())
    {
        return -2;
    }

    if(p_previous_timestep_state->m_state_variables.size() != p_previous_timestep_state_movements->size())
    {
        return -3;
    }

    *po_new_transition_movements = std::vector<ClMovement>(p_previous_timestep_state_movements->size());

    for(std::size_t variable_index=0; variable_index<p_previous_timestep_state->m_state_variables.size(); variable_index++)
    {
        float point1 = p_previous_timestep_state->m_state_variables[variable_index];
        float point2 = p_next_timestep_state->m_state_variables[variable_index];

        float new_velocity = (point2 - point1) / 1.0;  // Assuming time step is 1.0
        po_new_transition_movements->at(variable_index).m_velocity = new_velocity;

  
        /*
        *    Compute new acceleration
        */
        float acceleration_previous_timestep_velocity = 0.00;

        if(p_previous_timestep_state_movements != nullptr)
        {
            acceleration_previous_timestep_velocity = p_previous_timestep_state_movements->at(variable_index).m_velocity;
        }

        float new_acceleration = (new_velocity - acceleration_previous_timestep_velocity) / 1.0;  // Assuming time step is 1.0                
        po_new_transition_movements->at(variable_index).m_acceleration = new_acceleration;
    }

    return 1; 
}

int ClMovementLearner::GetTransition(ClStateChain* p_state_chain, CUSTOM_TRANSITION_DATA_POINTER& po_new_transition_data)
{
    if(p_state_chain == nullptr)
    {
        return -1;
    }

    /*
    *    We will create the instance, not the user
    */
    if(po_new_transition_data != nullptr)
    {
        return -2;
    }

    if(p_state_chain->m_blocks.size()==0)
    {
        return -3;
    }

    std:size_t number_of_variable = p_state_chain->m_blocks.back().m_state->m_state_variables.size();


    std::shared_ptr<std::vector<ClMovement>> po_new_movements = std::make_shared<std::vector<ClMovement>>(number_of_variable);

    if(p_state_chain->m_blocks.size()==1)
    {
        po_new_transition_data = po_new_movements;
        return 1;
    }

    STATE_POINTER& previous_state = p_state_chain->m_blocks[p_state_chain->m_blocks.size()-2].m_state;
    STATE_POINTER& current_state = p_state_chain->m_blocks[p_state_chain->m_blocks.size()-1].m_state;

    std::shared_ptr<std::vector<ClMovement>> previous_transition_movements = std::static_pointer_cast<std::vector<ClMovement>>(p_state_chain->m_blocks[p_state_chain->m_blocks.size()-2].m_transition->m_movement_learner_variables_transitions);

    if(previous_state->m_state_variables.size() != current_state->m_state_variables.size())
    {
        return -2;
    }

    if(previous_state->m_state_variables.size() != previous_transition_movements->size())
    {
        return -3;
    }

    int result = this->ComputeMovements(previous_state, previous_transition_movements, current_state, po_new_movements);
    if(result != 1)
    {
        return -4;
    }

    po_new_transition_data = po_new_movements;

    return 1;
}


// int ClMovementLearner::Predict(STATE_CHAIN_POINTER p_state_chain, float& po_predicted_value);
// int ClMovementLearner::Learn(STATE_CHAIN_POINTER p_state_chain, float p_predicted_value, float p_actual_value);