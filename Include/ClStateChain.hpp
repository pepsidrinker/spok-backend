#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "ClState.hpp"
#include "ClStateTransition.hpp"
#include "Learners/ClLearner.hpp"


class ClStateChain
{
    public:
    struct STATE_CHAIN_BLOCK
    {
        std::uint64_t m_timestep;
        std::shared_ptr<ClState> m_state;
        std::shared_ptr<ClStateTransition> m_transition;
        std::shared_ptr<ClState>  m_predictive_next_state;

        STATE_CHAIN_BLOCK()
        {
            this->m_timestep = 0;
            this->m_state = nullptr;
            this->m_transition = nullptr;
            this->m_predictive_next_state = nullptr;
        }
    };

    private:
        // static int PredictNextStateVariable(float p_variable_current_value, ClStateTransition::ClMovement& p_ClMovement, std::size_t p_number_of_timestep_in_the_future, float& po_variable_predicted_value);
        // int PredictNextState(STATE_POINTER p_state, STATE_TRANSITION_POINTER p_state_transition, STATE_POINTER& po_new_predictive_state);

    public:
        std::vector<STATE_CHAIN_BLOCK> m_blocks;
        

    public:
        //int AddState(std::shared_ptr<ClState> p_state);

        static int Create(std::shared_ptr<ClStateChain>& po_new_logic_block);
        void Print();
};

typedef std::shared_ptr<ClStateChain> STATE_CHAIN_POINTER;