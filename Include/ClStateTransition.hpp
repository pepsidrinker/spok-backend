#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "ClState.hpp"

class ClStateTransition
{
    public:
    struct POSITION
    {
        float m_previous_vector_x;
        float m_previous_vector_y;

        float m_next_vector_x;
        float m_next_vector_y;

        POSITION()
        {
            this->m_previous_vector_x = 0.00;
            this->m_previous_vector_y = 0.00;
            this->m_next_vector_x = 0.00;
            this->m_next_vector_y = 0.00;
        };
    };

    std::vector<POSITION> m_state_variables_transitions;

    ClStateTransition();
    ~ClStateTransition();
    static int Create(std::size_t p_number_of_variable, std::shared_ptr<ClStateTransition>& po_new_state_transition);
    void Print();
};

typedef std::shared_ptr<ClStateTransition> STATE_TRANSITION_POINTER;