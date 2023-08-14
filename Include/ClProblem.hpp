#pragma once

#include <memory>
#include <vector>

#include "ClState.hpp"
#include "ClOperator.hpp"


class ClProblem
{
    protected:

        STATE_POINTER m_source_state;
        STATE_POINTER m_destination_state;

        std::vector<OPERATOR_POINTER> m_operators;
        std::vector< std::shared_ptr<ClProblem> > m_sub_problems;
    public:
    


    ClProblem();
    ~ClProblem();
    int Solve();
    static std::shared_ptr<ClProblem> Create();
};

typedef std::shared_ptr<ClProblem> PROBLEM_POINTER;