#pragma once

#include "ClOperator.hpp"
#include "../ClState.hpp"

#include <memory>
#include <vector>
#include <string>

#include <xxhash.h>


class ClProblem
{
    public:
    typedef std::shared_ptr<ClProblem> PROBLEM_POINTER;
    typedef std::shared_ptr<std::vector<PROBLEM_POINTER>> PROBLEM_STORE_POINTER;    

    public:
        std::string m_uid;
        PROBLEM_STORE_POINTER m_previously_tried_hypotheses;
        PROBLEM_POINTER m_parent_problem;


        /*
        *    Initial state of the problem
        */
        STATE_POINTER m_problematic_state;
        STATE_POINTER m_wanted_state;

        /*
        *    New state which hypothetically closer to the solution
        */
        STATE_POINTER m_hypothetical_solution_state;
        std::vector<OPERATOR_POINTER> m_possible_operators;
        OPERATOR_POINTER m_chosen_operator;
   

        virtual int SolveUsingSpecifiedOperator(OPERATOR_POINTER p_possible_operator_position_to_apply);        

        virtual int IsEqualTo(ClProblem* p_source_problem);

        int GenerateUID(std::string& po_uid);
        
    public:
        ClProblem();
        ~ClProblem();

        //static int AddToProblemCluster(PROBLEM_CLUSTER_POINTER p_problem_cluster, PROBLEM_POINTER p_problem_to_add);       

        static int Create(STATE_POINTER p_current_state, std::vector<OPERATOR_POINTER>& p_possible_operators, STATE_POINTER p_wanted_state, PROBLEM_STORE_POINTER p_previously_tried_hypotheses, PROBLEM_POINTER p_parent_problem, PROBLEM_POINTER& po_problem_instance);        
        //static int DefaultIsSolvedFunction(ClOperator* p_operator_to_apply);

        int IsOperatorUsable(OPERATOR_POINTER p_operator);
        int GetUsableOperators(std::vector<OPERATOR_POINTER>& p_possible_operators, std::vector<OPERATOR_POINTER>& po_usable_operators);
        int ApplyOperator(OPERATOR_POINTER p_operator);                     

        /*
        *    Used to simulate get_instance
        */
        virtual int GetProblemTypeID();  
        virtual int IsEqualTo(PROBLEM_POINTER p_source_problem);
        virtual int AmIBeingSolvedSomewhereElse(PROBLEM_POINTER& po_identical_problem);

        virtual int IsInitialized();
        //virtual int CreateAndCloneTo(PROBLEM_POINTER& po_target_problem);
        virtual int Solve(PROBLEM_POINTER& po_last_solved_sub_problem);
        virtual int IsSolved();
};

typedef std::shared_ptr<ClProblem> PROBLEM_POINTER;
typedef std::shared_ptr<std::vector<PROBLEM_POINTER>> PROBLEM_STORE_POINTER; 
