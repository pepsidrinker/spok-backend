#include "ClStateChain.hpp"


int ClStateChain::Create(std::shared_ptr<ClStateChain>& po_new_logic_block)
{
    auto new_chain = std::make_shared<ClStateChain>();
    po_new_logic_block = new_chain;
    return 1;
}

int ClStateChain::AddState(std::shared_ptr<ClState> p_state)
{
    if(p_state == nullptr)
    {
        return -1;
    }


    STATE_CHAIN_BLOCK new_block;
    new_block.m_state = p_state;
    new_block.m_transition = nullptr;

    if(this->m_blocks.size()==0)
    {
        this->m_blocks.push_back(new_block);
        return 1;
    }

    int result = 0;

    result = ClStateTransition::Create(p_state->m_state_variables.size(),new_block.m_transition);
    if(result != 1)
    {
        return -2;
    }

    for(std::size_t i=0; i<this->m_learner_instances.size(); i++)
    {
        ClStateTransition::LEARNER_TRANSITION_INFORMATIONS learner_transition_informations;

        learner_transition_informations.m_learner_instance = this->m_learner_instances[i];
        result = this->m_learner_instances[i]->AddTimestep(p_state->m_state_variables,learner_transition_informations.m_learner_transition_data);

        new_block.m_transition->m_learners_transitions.push_back(learner_transition_informations);
    }

    this->m_blocks.push_back(new_block);
    
    return 1;
}

// int ClStateChain::PredictNextStateVariable(float p_variable_current_value, ClStateTransition::ClMovement& p_ClMovement, std::size_t p_number_of_timestep_in_the_future, float& po_variable_predicted_value)
// {
//     float predicted_value = 0.00;

//     predicted_value = p_variable_current_value + (p_ClMovement.m_velocity * p_number_of_timestep_in_the_future) + (0.5 * p_ClMovement.m_acceleration * p_number_of_timestep_in_the_future * p_number_of_timestep_in_the_future);
//     po_variable_predicted_value = predicted_value;

//     return 1;
// }

// int ClStateChain::PredictNextState(STATE_POINTER p_state, STATE_TRANSITION_POINTER p_state_transition, STATE_POINTER& po_new_predictive_state)
// {
//     if(p_state == nullptr || p_state_transition == nullptr)
//     {
//         return -1;
//     }

//     STATE_POINTER new_state = nullptr;
//     int result = ClState::Create(p_state->m_state_variables.size(), new_state);
//     if(result != 1)
//     {
//         return -2;
//     }

//     for(std::size_t i=0; i<p_state->m_state_variables.size(); i++)
//     {
//         result = PredictNextStateVariable(p_state->m_state_variables[i],p_state_transition->m_state_variables_transitions[i],1,new_state->m_state_variables[i]);
//         if(result != 1)
//         {
//             return -3;
//         }
//     }

//     po_new_predictive_state = new_state;
//     return 1;
// }

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
