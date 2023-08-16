#include "ClStateTransition.hpp"

ClStateTransition::ClStateTransition()
{
}

ClStateTransition::~ClStateTransition()
{
}

int ClStateTransition::Create(std::size_t p_number_of_variable, std::shared_ptr<ClStateTransition>& po_new_state_transition)
{
    auto new_state_transition = std::make_shared<ClStateTransition>();
    new_state_transition->m_state_variables_transitions = std::vector<MOVEMENT>(p_number_of_variable);
    po_new_state_transition = new_state_transition;
    return 1;
}

int ClStateTransition::Compute(STATE_POINTER p_previous_timestep_state, std::shared_ptr<ClStateTransition> p_previous_timestep_state_transition, STATE_POINTER p_next_timestep_state, std::shared_ptr<ClStateTransition>& po_new_transition_pointer)
{
    if(p_previous_timestep_state == nullptr || p_previous_timestep_state_transition == nullptr || p_next_timestep_state == nullptr)
    {
        return -1;
    }

    if(p_previous_timestep_state->m_state_variables.size() != p_next_timestep_state->m_state_variables.size() || p_previous_timestep_state->m_state_variables.size() != p_previous_timestep_state_transition->m_state_variables_transitions.size())
    {
        return -2;
    }



    STATE_TRANSITION_POINTER new_state_transition_instance = nullptr;
    if(ClStateTransition::Create(p_previous_timestep_state->m_state_variables.size(), new_state_transition_instance)!=1)
    {
        return -3;
    }

    for(std::size_t variable_index=0; variable_index<p_previous_timestep_state->m_state_variables.size(); variable_index++)
    {
        ClState::POSITION& point1 = p_previous_timestep_state->m_state_variables[variable_index];
        ClState::POSITION& point2 = p_next_timestep_state->m_state_variables[variable_index];

        float deltaX = point2.m_x - point1.m_x;
        float deltaY = point2.m_y - point1.m_y;

        // Calculate the magnitude direction using the Pythagorean theorem
        new_state_transition_instance->m_state_variables_transitions[variable_index].m_velocity_direction_x = deltaX;
        new_state_transition_instance->m_state_variables_transitions[variable_index].m_velocity_direction_y = deltaY;
        new_state_transition_instance->m_state_variables_transitions[variable_index].m_velocity_speed = std::sqrt(deltaX * deltaX + deltaY * deltaY);


        float accelerationX = (deltaX - p_previous_timestep_state_transition->m_state_variables_transitions[variable_index].m_velocity_direction_x);
        float accelerationY = (deltaY - p_previous_timestep_state_transition->m_state_variables_transitions[variable_index].m_velocity_direction_y);

        // Calculate the acceleration using the Pythagorean theorem
        new_state_transition_instance->m_state_variables_transitions[variable_index].m_accelration_direction_x = accelerationX;
        new_state_transition_instance->m_state_variables_transitions[variable_index].m_accelration_direction_y = accelerationY;
        new_state_transition_instance->m_state_variables_transitions[variable_index].m_acceleration_speed = std::sqrt(accelerationX * accelerationX + accelerationY * accelerationY);

        po_new_transition_pointer = new_state_transition_instance;
    }

    return 1; 
}


void ClStateTransition::Print()
{
    // std::cout << "==== Printing state transition ====" << std::endl;
    // for (std::size_t i=0; i<this->m_state_variables_transitions.size(); i++) 
    // {
    //     std::cout << "[" << i << "] : [" << this->m_state_variables_transitions[i].m_previous_vector_x << ", " << this->m_state_variables_transitions[i].m_previous_vector_y << " => " << this->m_state_variables_transitions[i].m_next_vector_x << ", " << this->m_state_variables_transitions[i].m_next_vector_y << "]" << std::endl;
    // }
    // std::cout << std::endl << "==== End of state transition ====" << std::endl;    
}