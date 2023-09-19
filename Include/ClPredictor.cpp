#include "ClPredictor.hpp"

ClPredictor::ClPredictor(){}
ClPredictor::~ClPredictor(){}


int ClPredictor::Create(STATE_CHAIN_POINTER p_state_chain, std::shared_ptr<ClPredictor>& po_new_instance)
{
    if(p_state_chain == nullptr)
    {
        return -1;
    }

    po_new_instance = std::make_shared<ClPredictor>();
    po_new_instance->m_state_chain = p_state_chain;
    po_new_instance->m_last_processed_state_chain_block_index = 0;

    int result = ClMovementLearner::Create(po_new_instance->m_movement_learner);
    if(result != 1)
    {
        std::cout << "[ClPredictor::Create] Error running [ClMovementLearner::Create] with result [" << result << "]" << std::endl;
        return -2;        
    }    

    return 1;
}

int ClPredictor::ProcessUpdatesFromStateChain()
{
    if(this->m_state_chain == nullptr)
    {
        return -1;
    }

    if(this->m_state_chain->m_blocks.size() == 0)
    {
        return 1;
    }

    if(this->m_last_processed_state_chain_block_index >= this->m_state_chain->m_blocks.size()-1)
    {
        return 1;
    }

    int result = 0;

    for(std::size_t i=this->m_last_processed_state_chain_block_index+1; i<this->m_state_chain->m_blocks.size(); i++)
    {
        ClStateChain::STATE_CHAIN_BLOCK& left_block = this->m_state_chain->m_blocks[i-1];
        ClStateChain::STATE_CHAIN_BLOCK& right_block = this->m_state_chain->m_blocks[i];

        /*
        *    Run the movement predictor
        */
        ClStateTransition::LEARNER_TRANSITION_INFORMATIONS movement_learner_transition_informations;
        movement_learner_transition_informations.m_learner_instance = this->m_movement_learner;

        result = this->m_movement_learner->AddTimestep(right_block.m_state->m_state_variables,movement_learner_transition_informations.m_learner_transition_data);
        if(result != 1)
        {
            return -2;
        }


        left_block.m_transition->m_learners_transitions.push_back(movement_learner_transition_informations);
        this->m_last_processed_state_chain_block_index = i;
    }

    return 1;
}


int ClPredictor::PredictNextState(STATE_POINTER& po_next_state, std::size_t p_number_of_timestep_in_the_future)
{
    ClStateChain::STATE_CHAIN_BLOCK& last_block = this->m_state_chain->m_blocks.back();
    STATE_POINTER prediction_state = nullptr;
    int result = 0;

    result = ClState::Create(last_block.m_state->m_state_variables.size(),prediction_state);
    if(result != 1)
    {
        std::cout << "[ClPredictor::PredictNextState] Error running [ClState::Create] with result [" << result << "]" << std::endl;
        return -1;
    }

    result = this->m_movement_learner->PredictNextStateVariables(prediction_state->m_state_variables,p_number_of_timestep_in_the_future);
    if(result != 1)
    {
        std::cout << "[ClPredictor::PredictNextState] Error running [ClMovementLearner::PredictNextStateVariables] with result [" << result << "]" << std::endl;
        return -2;
    }

    po_next_state = prediction_state;
    return 1;
}