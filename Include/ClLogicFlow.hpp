#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "ClState.hpp"
#include "ClStateTransition.hpp"

/*
    A logic flow represent a sequence of states through time, and their transitions
    1 element in the vector = 1 timestep
*/

class ClLogicFlow
{
    struct LOGIC_FLOW_BLOCK
    {
        STATE_POINTER m_state;
        STATE_TRANSITION_POINTER m_transition;
        STATE_POINTER m_predictive_next_state;

        LOGIC_FLOW_BLOCK()
        {
            this->m_state = nullptr;
            this->m_transition = nullptr;
            this->m_predictive_next_state = nullptr;
        }
    };

    private:
        static int PredictNextStateVariable(const ClState::POSITION& p_initial_position, const ClStateTransition::MOVEMENT& p_movement, std::size_t p_number_of_timestep_in_the_future, ClState::POSITION& po_predicted_position);
        int PredictNextState(STATE_POINTER p_state, STATE_TRANSITION_POINTER p_state_transition, STATE_POINTER& po_new_predictive_state);

    public:
        std::vector<LOGIC_FLOW_BLOCK> m_blocks;

    public:
        int AddState(std::shared_ptr<ClState> p_state);

        static int Create(std::shared_ptr<ClLogicFlow>& po_new_logic_block);
        void Print();
};

typedef std::shared_ptr<ClLogicFlow> LOGIC_FLOW_POINTER;