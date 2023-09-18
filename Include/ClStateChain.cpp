#include "ClStateChain.hpp"


int ClStateChain::Create(std::shared_ptr<ClStateChain>& po_new_logic_block)
{
    auto new_chain = std::make_shared<ClStateChain>();
    po_new_logic_block = new_chain;
    return 1;
}

// int ClStateChain::AddState(std::shared_ptr<ClState> p_state)
// {
    // if(p_state == nullptr)
    // {
    //     return -1;
    // }


    // STATE_CHAIN_BLOCK new_block;
    // new_block.m_state = p_state;
    // new_block.m_transition = nullptr;

    // if(this->m_blocks.size()==0)
    // {
    //     this->m_blocks.push_back(new_block);
    //     return 1;
    // }

    // int result = 0;

    // result = ClStateTransition::Create(p_state->m_state_variables.size(),new_block.m_transition);
    // if(result != 1)
    // {
    //     return -2;
    // }

    // for(std::size_t i=0; i<this->m_learner_instances.size(); i++)
    // {
    //     ClStateTransition::LEARNER_TRANSITION_INFORMATIONS learner_transition_informations;

    //     learner_transition_informations.m_learner_instance = this->m_learner_instances[i];

    //     result = this->m_learner_instances[i]->AddTimestep(p_state->m_state_variables,learner_transition_informations.m_learner_transition_data);
    //     if(result != 1)
    //     {
    //         return -3;
    //     }

    //     result = ClState::Create(p_state->m_state_variables.size(), learner_transition_informations.m_next_timestep_predictive_state);
    //     if(result != 1)
    //     {
    //         return -4;
    //     }


    //     result = this->m_learner_instances[i]->PredictNextStateVariables(learner_transition_informations.m_next_timestep_predictive_state->m_state_variables,1);
    //     if(result != 1)
    //     {
    //         return -5;
    //     }

    //     new_block.m_transition->m_learners_transitions.push_back(learner_transition_informations);
    // }


    // /*
    // *    Use the most accurate algorithm available as the chosen next predictive state
    // */
    // if(new_block.m_transition->m_learners_transitions.size() > 0)
    // {
    //     new_block.m_predictive_next_state = new_block.m_transition->m_learners_transitions.back().m_next_timestep_predictive_state;
    // }

    // this->m_blocks.push_back(new_block);
    
    // return 1;
//}

STATE_CHAIN_POINTER ClStateChain::Clone()
{
    std::vector<STATE_CHAIN_BLOCK> cloned_blocks;

    for(std::size_t i=0; i<this->m_blocks.size(); i++)
    {
        STATE_CHAIN_BLOCK new_block;
        new_block.m_timestep = this->m_blocks[i].m_timestep;
        new_block.m_state = this->m_blocks[i].m_state->Clone();
        new_block.m_transition = this->m_blocks[i].m_transition->Clone();
        new_block.m_predictive_next_state = this->m_blocks[i].m_predictive_next_state->Clone();
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
