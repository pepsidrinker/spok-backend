#pragma once

#include "ClOperator.hpp"
#include "../ClState.hpp"
#include "../ClStateChain.hpp"
#include "../ClPredictor.hpp"
#include "ClHypothesis.hpp"
#include "ClHypothesisStore.hpp"

#include <memory>
#include <vector>
#include <string>

#include <xxhash.h>



class ClProblem : public std::enable_shared_from_this<ClProblem>
{
    public:
    typedef std::shared_ptr<ClProblem> PROBLEM_POINTER;
    typedef float (*PROBLEM_SOLUTION_DISTANCE_FUNCTION_POINTER)(ClProblem* p_problem, STATE_POINTER p_state_to_evaluate);

    public:
        HYPOTHESIS_STORE_POINTER m_global_hypothesis_store;

        std::vector<ClHypothesis> m_hypotheses;
        PREDICTOR_POINTER m_predictor;

        PROBLEM_POINTER m_parent_problem;
        PROBLEM_SOLUTION_DISTANCE_FUNCTION_POINTER m_solution_distance_function;


        /*
        *    Initial state of the problem
        */
        STATE_CHAIN_POINTER m_state_chain;
        float m_hypothetical_solution_distance;

        std::vector<OPERATOR_POINTER> m_possible_operators;
   
        virtual int IsEqualTo(ClProblem* p_source_problem);

        std::string GetUID();
        
    public:
        ClProblem();
        virtual ~ClProblem();

        bool IsInitialized();

        int HasHypothesisBeenTriedBefore(ClHypothesis& p_hypothesis);
        int ComputeHypothesesPredictiveState();
        int GetHypothesesIndexesThatSolvedProblem(std::vector<std::size_t>& po_solved_hypotheses_indexes);

        static int Create(STATE_CHAIN_POINTER p_state_chain, std::vector<OPERATOR_POINTER>& p_possible_operators, PROBLEM_SOLUTION_DISTANCE_FUNCTION_POINTER p_solution_distance_function, HYPOTHESIS_STORE_POINTER p_hypotheses_store, PREDICTOR_POINTER p_predictor, PROBLEM_POINTER p_parent_problem, PROBLEM_POINTER& po_problem_instance);               
    
        int IsOperatorUsable(OPERATOR_POINTER p_operator);
        int GetUsableOperators(std::vector<OPERATOR_POINTER>& p_possible_operators, std::vector<OPERATOR_POINTER>& po_usable_operators);                  

        /*
        *    Used to simulate get_instance
        */
        virtual int IsEqualTo(PROBLEM_POINTER p_source_problem);
        virtual int ProposeOperatorToGetCloserToSolution(OPERATOR_POINTER& po_proposed_operator, std::size_t p_number_of_steps_to_foresee);

};

typedef std::shared_ptr<ClProblem> PROBLEM_POINTER;
typedef int (*PROBLEM_SOLUTION_DISTANCE_FUNCTION_POINTER)(ClProblem* p_problem, STATE_POINTER p_state_to_evaluate);