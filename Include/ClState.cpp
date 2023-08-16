#include "ClState.hpp"

ClState::ClState()
{
}

ClState::~ClState()
{
}

int ClState::Create(std::size_t p_number_of_variable, std::shared_ptr<ClState>& po_new_state)
{
    auto new_state = std::make_shared<ClState>();
    new_state->m_state_variables = std::vector<POSITION>(p_number_of_variable);
    po_new_state = new_state;
    return 1;
}


void ClState::Print()
{
    std::cout << "==== Printing state ====" << std::endl;
    for (std::size_t i=0; i<this->m_state_variables.size(); i++) 
    {
        std::cout << "[" << i << "] : [" << this->m_state_variables[i].m_x << ", " << this->m_state_variables[i].m_y << "]" << std::endl;
    }
    std::cout << std::endl << "==== End of state ====" << std::endl;    
}