#pragma once

#include "ClOperator.hpp"
#include "../ClState.hpp"

#include <memory>
#include <string>

#include <xxhash.h>



class ClHypothesis
{
    public:
        ClHypothesis();
        ~ClHypothesis();
        std::shared_ptr<ClState> m_current_state;
        std::shared_ptr<ClOperator> m_operator;
        std::shared_ptr<ClState> m_predictive_state;
        float m_predictive_state_solution_distance;

        std::string GetUID();
};