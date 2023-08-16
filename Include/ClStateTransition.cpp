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
    new_state_transition->m_state_variables_transitions = std::vector<POSITION>(p_number_of_variable);
    po_new_state_transition = new_state_transition;
    return 1;
}


void ClStateTransition::Print()
{
    std::cout << "==== Printing state transition ====" << std::endl;
    for (std::size_t i=0; i<this->m_state_variables_transitions.size(); i++) 
    {
        std::cout << "[" << i << "] : [" << this->m_state_variables_transitions[i].m_previous_vector_x << ", " << this->m_state_variables_transitions[i].m_previous_vector_y << " => " << this->m_state_variables_transitions[i].m_next_vector_x << ", " << this->m_state_variables_transitions[i].m_next_vector_y << "]" << std::endl;
    }
    std::cout << std::endl << "==== End of state transition ====" << std::endl;    
}