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

#include <mori/ClCedrusLibani.hpp>
#include <mori/ClCedrusLibaniTopologicIteratorDepthFirst.hpp>


#include <memory>


class ClIntelligenceUnit
{
    typedef std::shared_ptr<ClIntelligenceUnit> INTELLIGENCE_UNIT_POINTER;

    protected:
        int AddNewBlockToStateChain(STATE_POINTER& p_state);

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
        int ProposeOperatorToGetCloserToSolution(OPERATOR_POINTER& po_proposed_operator, std::size_t p_number_of_steps_to_foresee);
};

typedef std::shared_ptr<ClIntelligenceUnit> INTELLIGENCE_UNIT_POINTER;