#include "ClStateTransition.hpp"

ClStateTransition::ClStateTransition()
{
}

ClStateTransition::~ClStateTransition()
{
}

int ClStateTransition::Create(std::size_t p_number_of_variable, std::shared_ptr<ClStateTransition>& po_new_state_transition)
{
    po_new_state_transition = std::make_shared<ClStateTransition>();
    return 1;
}


// int ClStateTransition::GetLearnerTransitionDataByLearnerType(unsigned short p_learner_type, LEARNER_TRANSITION_INFORMATIONS& po_learner_transition_informations)
// {
//     for(std::size_t i=0; i<this->m_learners_transitions.size(); i++)
//     {
//         if(this->m_learners_transitions[i].m_learner_instance->LEARNER_TYPE == p_learner_type)
//         {
//             po_learner_transition_informations = this->m_learners_transitions[i];
//             return 1;
//         }
//     }

//     return -1;
// }

// int ClStateTransition::Compute(STATE_POINTER p_previous_timestep_state, std::shared_ptr<ClStateTransition> p_previous_timestep_state_transition, STATE_POINTER p_next_timestep_state, std::shared_ptr<ClStateTransition>& po_new_transition_pointer)
// {
//     if(p_previous_timestep_state == nullptr || p_next_timestep_state == nullptr)
//     {
//         return -1;
//     }

//     if(p_previous_timestep_state->m_state_variables.size() != p_next_timestep_state->m_state_variables.size())
//     {
//         return -2;
//     }

//     STATE_TRANSITION_POINTER new_state_transition_instance = nullptr;
//     if(ClStateTransition::Create(p_previous_timestep_state->m_state_variables.size(), new_state_transition_instance)!=1)
//     {
//         return -3;
//     }

//     for(std::size_t variable_index=0; variable_index<p_previous_timestep_state->m_state_variables.size(); variable_index++)
//     {
//         float point1 = p_previous_timestep_state->m_state_variables[variable_index];
//         float point2 = p_next_timestep_state->m_state_variables[variable_index];

//         float new_velocity = (point2 - point1) / 1.0;  // Assuming time step is 1.0
//         new_state_transition_instance->m_state_variables_transitions[variable_index].m_velocity = new_velocity;

  
//         /*
//         *    Compute new acceleration
//         */
//         float acceleration_previous_timestep_velocity = 0.00;

//         if(p_previous_timestep_state_transition != nullptr)
//         {
//             acceleration_previous_timestep_velocity = p_previous_timestep_state_transition->m_state_variables_transitions[variable_index].m_velocity;
//         }

//         float new_acceleration = (new_velocity - acceleration_previous_timestep_velocity) / 1.0;  // Assuming time step is 1.0                
//         new_state_transition_instance->m_state_variables_transitions[variable_index].m_acceleration = new_acceleration;



//         po_new_transition_pointer = new_state_transition_instance;
//     }

//     return 1; 
// }


// void ClStateTransition::Print()
// {
//     std::cout << "==== Printing state transition ====" << std::endl;
//     std::shared_ptr<std::vector<ClMovement>> movements = std::static_pointer_cast<std::vector<ClMovement>>(this->m_movement_learner_variables_transitions);

//     for (std::size_t i=0; i<this->m_movement_learner_variables_transitions.size(); i++) 
//     {
//         std::cout << "[" << i << "] : [Velocity :" << this->m_state_variables_transitions[i].m_velocity << "], [Acceleration : " << this->m_state_variables_transitions[i].m_acceleration << "]"  << std::endl;
//     }
//     std::cout << std::endl << "==== End of state transition ====" << std::endl;    
// }