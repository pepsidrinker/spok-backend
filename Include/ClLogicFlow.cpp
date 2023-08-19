#include "ClLogicFlow.hpp"


int ClLogicFlow::Create(std::shared_ptr<ClLogicFlow>& po_new_logic_block)
{
    auto new_chain = std::make_shared<ClLogicFlow>();
    po_new_logic_block = new_chain;
    return 1;
}

int ClLogicFlow::AddState(std::shared_ptr<ClState> p_state)
{
    if(p_state == nullptr)
    {
        return -1;
    }


    LOGIC_FLOW_BLOCK new_block;
    new_block.m_state = p_state;
    new_block.m_transition = nullptr;

    if(this->m_blocks.size()==0)
    {
        this->m_blocks.push_back(new_block);
        return 1;
    }

    STATE_POINTER& previous_state = this->m_blocks.back().m_state;
    STATE_TRANSITION_POINTER previous_state_transition = this->m_blocks.back().m_transition;

    if(previous_state->m_state_variables.size() != p_state->m_state_variables.size())
    {
        return -2;
    }


    STATE_TRANSITION_POINTER new_state_transition = nullptr;
    int result = ClStateTransition::Create(p_state->m_state_variables.size(),new_state_transition);
    if(result != 1)
    {
        return -3;
    }

    result = ClStateTransition::Compute(previous_state,previous_state_transition,p_state,new_state_transition);
    if(result != 1)
    {
        return -4;
    }

    new_block.m_transition = new_state_transition;
    this->m_blocks.push_back(new_block);
    
    return 1;
}

void ClLogicFlow::Print()
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
            this->m_blocks[i].m_transition->Print();
        }                
    }
    std::cout << std::endl << "==== End of logic flow ====" << std::endl;
}
