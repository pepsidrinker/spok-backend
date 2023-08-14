#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "ClState.hpp"

/*
    A state chain represent a sequence of states through time.
    1 element in the vector = 1 timestep
*/

class ClStateChain
{
    public:
        std::vector<STATE_POINTER> m_states;
        
        static int Create(std::shared_ptr<ClStateChain>& po_new_state_chain);
        void Print();
};

typedef std::shared_ptr<ClStateChain> STATE_CHAIN_POINTER;