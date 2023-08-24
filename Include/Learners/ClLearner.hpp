#pragma once

#include "../ClStateChain.hpp"
#include "../ClStateTransition.hpp"
#include <memory>

class ClStateChain;

class ClLearner
{
    public:
        virtual int GetTransition(ClStateChain* p_state_chain, CUSTOM_TRANSITION_DATA_POINTER& po_new_transition_data) = 0;
        virtual ~ClLearner();
        virtual void Print(CUSTOM_TRANSITION_DATA_POINTER p_transition_data) = 0;
};