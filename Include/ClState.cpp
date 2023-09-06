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
    new_state->m_state_variables = std::vector<float>(p_number_of_variable);
    po_new_state = new_state;
    return 1;
}


void ClState::Print()
{
    std::cout << "==== Printing state of [" << this->m_state_variables.size() << "] variable(s) ====" << std::endl;
    for (std::size_t i=0; i<this->m_state_variables.size(); i++) 
    {
        std::cout << "[" << i << "] : [" << this->m_state_variables[i] << "]" << std::endl;
    }
    std::cout << std::endl << "==== End of state ====" << std::endl;    
}

bool ClState::IsEqualTo(const ClState& p_state)
{
    if (this->m_state_variables.size() != p_state.m_state_variables.size())
    {
        return false;
    }

    for (size_t i = 0; i < this->m_state_variables.size(); ++i)
    {
        if (this->m_state_variables[i] != p_state.m_state_variables[i])
        {
            return false;
        }
    }

    return true;
}