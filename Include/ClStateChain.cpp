#include "ClStateChain.hpp"


int ClStateChain::Create(std::shared_ptr<ClStateChain>& po_new_logic_block)
{
    auto new_chain = std::make_shared<ClStateChain>();
    po_new_logic_block = new_chain;
    return 1;
}

STATE_CHAIN_POINTER ClStateChain::Clone()
{
    std::vector<STATE_CHAIN_BLOCK> cloned_blocks;

    for(std::size_t i=0; i<this->m_blocks.size(); i++)
    {
        STATE_CHAIN_BLOCK new_block;
        new_block.m_timestep = this->m_blocks[i].m_timestep;
        
        if(this->m_blocks[i].m_state != nullptr)
        {
            new_block.m_state = this->m_blocks[i].m_state->Clone();
        }

        if(this->m_blocks[i].m_transition != nullptr)
        {
            new_block.m_transition = this->m_blocks[i].m_transition->Clone();
        }

        if(this->m_blocks[i].m_predictive_next_state != nullptr)
        {
            new_block.m_predictive_next_state = this->m_blocks[i].m_predictive_next_state->Clone();
        }

        cloned_blocks.push_back(new_block);
    }

    STATE_CHAIN_POINTER cloned_state_chain = nullptr;
    int result = ClStateChain::Create(cloned_state_chain);
    if(result != 1)
    {
        std::cout << "[ClStateChain::Clone] Error while cloning state chain" << std::endl;
        return nullptr;
    }

    cloned_state_chain->m_blocks = cloned_blocks;
    return cloned_state_chain;
}

void ClStateChain::Print()
{
    std::cout << "==== Printing logic flow ====" << std::endl;
    for (unsigned int i = 0; i < this->m_blocks.size(); i++)
    {
        std::cout << "Block [" << (i+1) << "] out of [" <<  this->m_blocks.size() << "]" << std::endl;
        if(this->m_blocks[i].m_state != nullptr)
        {
            this->m_blocks[i].m_state->Print();
        }

        if(this->m_blocks[i].m_transition != nullptr)
        {
            //this->m_blocks[i].m_transition->Print();
        }    

        if(this->m_blocks[i].m_predictive_next_state != nullptr)
        {
            this->m_blocks[i].m_predictive_next_state->Print();
        }              
    }
    std::cout << std::endl << "==== End of logic flow ====" << std::endl;
}
