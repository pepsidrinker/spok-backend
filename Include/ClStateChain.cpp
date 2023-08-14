#include "ClStateChain.hpp"


int ClStateChain::Create(std::shared_ptr<ClStateChain>& po_new_state_chain)
{
    auto new_chain = std::make_shared<ClStateChain>();
    po_new_state_chain = new_chain;
    return 1;
}

void ClStateChain::Print()
{
    std::cout << "==== Printing state chain ====" << std::endl;
    for (unsigned int i = 0; i < this->m_states.size(); i++)
    {
        this->m_states[i]->Print();
    }
    std::cout << std::endl << "==== End of state chain ====" << std::endl;
}