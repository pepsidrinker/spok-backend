#pragma once

#include <memory>

#include "ClOperator.hpp"
#include "../ClState.hpp"

#include <memory>


class ClHypothesis
{
    public:
        ClHypothesis();
        ~ClHypothesis();
        std::shared_ptr<ClOperator> m_operator;
        std::shared_ptr<ClState> m_predictive_state;
};