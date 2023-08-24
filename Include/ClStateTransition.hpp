#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include <cmath>

#include "ClState.hpp"
#include <memory>

class ClStateTransition
{
    public:
        std::shared_ptr<void> m_movement_learner_variables_transitions;

        ClStateTransition();
        ~ClStateTransition();
        static int Create(std::size_t p_number_of_variable, std::shared_ptr<ClStateTransition>& po_new_state_transition);
        //void Print();
};

typedef std::shared_ptr<void> CUSTOM_TRANSITION_DATA_POINTER;
typedef std::shared_ptr<ClStateTransition> STATE_TRANSITION_POINTER;