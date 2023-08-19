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

        LOGIC_FLOW_BLOCK()
        {
            this->m_state = nullptr;
            this->m_transition = nullptr;
        }
    };

    public:
        std::vector<LOGIC_FLOW_BLOCK> m_blocks;

    public:
        int AddState(std::shared_ptr<ClState> p_state);
        static int Create(std::shared_ptr<ClLogicFlow>& po_new_logic_block);
        void Print();
};

typedef std::shared_ptr<ClLogicFlow> LOGIC_FLOW_POINTER;