#pragma once

#include <memory>
#include <vector>

#include "ClState.hpp"
#include "ClOperator.hpp"


class ClSolver
{
    protected:

        STATE_POINTER m_source_state;
        STATE_POINTER m_destination_state;

        std::vector<OPERATOR_POINTER> m_operators;

    public:
    
    ClSolver();
    ~ClSolver();
    int FindNewOperator();
    static int Create(std::shared_ptr<ClSolver>& po_new_solver);
};

typedef std::shared_ptr<ClSolver> SOLVER_POINTER;