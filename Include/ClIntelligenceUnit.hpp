#pragma once

/*
*    This class handle everything : it's the one the main loop will be querying.
*/

#include "ClState.hpp"
#include "ClStateChain.hpp"

#include "ProblemSolving/ClOperator.hpp"
#include "ProblemSolving/ClProblem.hpp"
#include "ProblemSolving/ClProblemStore.hpp"

#include "Learners/Movement/ClMovementLearner.hpp"


#include <memory>


class ClIntelligenceUnit
{
    typedef std::shared_ptr<ClIntelligenceUnit> INTELLIGENCE_UNIT_POINTER;

    public:
        STATE_CHAIN_POINTER m_state_chain;
        PROBLEM_STORE_POINTER m_problem_store;
        PROBLEM_POINTER m_problem;
        std::vector<OPERATOR_POINTER> m_possible_operators;
        ClProblem::PROBLEM_SOLUTION_DISTANCE_FUNCTION_POINTER m_solution_distance_function;

        MOVEMENT_LEARNER_POINTER m_movement_learner;


        ClIntelligenceUnit();
        ~ClIntelligenceUnit();

        bool IsInitialized();

        static int Create(std::vector<OPERATOR_POINTER>& p_possible_operators, ClProblem::PROBLEM_SOLUTION_DISTANCE_FUNCTION_POINTER p_solution_distance_function, INTELLIGENCE_UNIT_POINTER& po_intelligence_unit_instance);
        int AddNewTimestep(STATE_POINTER& p_state);
        int ProposeSolution(STATE_CHAIN_POINTER& po_solution_state_chain);
};

typedef std::shared_ptr<ClIntelligenceUnit> INTELLIGENCE_UNIT_POINTER;