#pragma once

#include "ClProblemStore.hpp"
#include "ClOperator.hpp"
#include "../ClState.hpp"
#include "../ClStateChain.hpp"

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
        PROBLEM_STORE_POINTER m_previously_tried_hypotheses;
        PROBLEM_POINTER m_parent_problem;
        PROBLEM_SOLUTION_DISTANCE_FUNCTION_POINTER m_solution_distance_function;


        /*
        *    Initial state of the problem
        */
        STATE_CHAIN_POINTER m_state_chain;

        /*
        *    New state which hypothetically closer to the solution
        */
        STATE_POINTER m_hypothetical_solution_state;
        float m_hypothetical_solution_distance;

        std::vector<OPERATOR_POINTER> m_possible_operators;
        OPERATOR_POINTER m_chosen_operator;
   

        virtual int SolveUsingSpecifiedOperator(OPERATOR_POINTER p_possible_operator_position_to_apply);        

        virtual int IsEqualTo(ClProblem* p_source_problem);

        std::string GetUID();
        
    public:
        ClProblem();
        ~ClProblem();

        bool IsInitialized();

        //static int AddToProblemCluster(PROBLEM_CLUSTER_POINTER p_problem_cluster, PROBLEM_POINTER p_problem_to_add);       

        static int Create(STATE_CHAIN_POINTER p_state_chain, std::vector<OPERATOR_POINTER>& p_possible_operators, PROBLEM_SOLUTION_DISTANCE_FUNCTION_POINTER p_solution_distance_function, PROBLEM_STORE_POINTER p_previously_tried_hypotheses, PROBLEM_POINTER p_parent_problem, PROBLEM_POINTER& po_problem_instance);        
        // static int Create(STATE_CHAIN_POINTER p_state_chain, std::vector<OPERATOR_POINTER>& p_possible_operators, PROBLEM_SOLUTION_DISTANCE_FUNCTION_POINTER p_solution_distance_function, PROBLEM_STORE_POINTER p_previously_tried_hypotheses, ClProblem* p_parent_problem, PROBLEM_POINTER& po_problem_instance);        
        //static int DefaultIsSolvedFunction(ClOperator* p_operator_to_apply);

        int IsOperatorUsable(OPERATOR_POINTER p_operator);
        int GetUsableOperators(std::vector<OPERATOR_POINTER>& p_possible_operators, std::vector<OPERATOR_POINTER>& po_usable_operators);
        int ApplyOperator(OPERATOR_POINTER p_operator);                     
        float GetCurrentStateSolutionDistance();

        /*
        *    Used to simulate get_instance
        */
        virtual int IsEqualTo(PROBLEM_POINTER p_source_problem);
        virtual int AmIBeingSolvedSomewhereElse(PROBLEM_POINTER& po_identical_problem);

        //virtual int IsInitialized();
        //virtual int CreateAndCloneTo(PROBLEM_POINTER& po_target_problem);
        virtual int ProposeSolution(PROBLEM_POINTER& po_last_solved_sub_problem);
        virtual int IsSolved();
};

typedef std::shared_ptr<ClProblem> PROBLEM_POINTER;
typedef int (*PROBLEM_SOLUTION_DISTANCE_FUNCTION_POINTER)(ClProblem* p_problem, STATE_POINTER p_state_to_evaluate);