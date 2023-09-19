#include "ClProblem.hpp"

ClProblem::ClProblem()
{
    this->m_state_chain = nullptr;
    this->m_solution_distance_function = nullptr;
    this->m_hypothetical_solution_state = nullptr;
    //this->m_previously_tried_hypotheses = nullptr;
    this->m_parent_problem = nullptr;
    this->m_chosen_operator = nullptr;
    this->m_hypothetical_solution_distance = std::numeric_limits<float>::max();
    this->m_hypotheses_tree = nullptr;
    this->m_current_hypothesis_tree_node = 0;
}

ClProblem::~ClProblem()
{

}

std::string ClProblem::GetUID()
{
    if(this->m_state_chain == nullptr || this->m_state_chain->m_blocks.size() == 0)
    {
        return "INVALID_UID";
    }

    STATE_POINTER problematic_state = this->m_state_chain->m_blocks.back().m_state;
    XXH64_hash_t problematic_state_hash = XXH64(problematic_state->m_state_variables.data(), problematic_state->m_state_variables.size() * sizeof(float), 0);

    std::string result = std::to_string(problematic_state_hash);    

    if(this->m_chosen_operator != nullptr)
    {
        result.append("-");
        result.append(this->m_chosen_operator->m_uid);
    }

    return result;
}


float ClProblem::GetCurrentStateSolutionDistance()
{
    if(this->m_solution_distance_function == nullptr)
    {
        return -1.00;
    }

    STATE_POINTER& current_state = this->m_state_chain->m_blocks.back().m_state;
    return this->m_solution_distance_function(this,current_state);
}

// int ClProblem::AddToProblemCluster(PROBLEM_CLUSTER_POINTER p_problem_cluster, PROBLEM_POINTER p_problem_to_add)
// {
//     if(p_problem_cluster == nullptr)
//     {
//         return -1;
//     }    

//     if(p_problem_cluster->IsInitialized()!=1)
//     {
//         return -1;
//     }        

//     if(p_problem_cluster->IsInitialized()!=1)
//     {
//         return -1;
//     }

//     std::unique_lock<std::shared_mutex> unique_block_guard(p_problem_cluster->m_mutex);
//     p_problem_cluster->m_problems.push_back(p_problem_to_add);

//     return 1;
// }

// int ClProblem::IsInitialized()
// {
//     if(this->m_problematic_state == nullptr)
//     {
//         return -3;
//     }

//     if(this->m_problematic_state->IsInitialized()!=1)
//     {
//         return -4;
//     }

//     if(this->m_hypothetical_solution_state == nullptr)
//     {
//         return -5;
//     }

//     if(this->m_hypothetical_solution_state->IsInitialized()!=1)
//     {
//         return -6;
//     }

//     // if(this->m_possible_operators.size()==0)
//     // {
//     //     return -7;
//     // }

//     for(std::size_t i=0; i<this->m_possible_operators.size(); i++)
//     {
//         if(this->m_possible_operators[i]->IsInitialized()!=1)
//         {
//             return -8;
//         }
//     }

//     if(this->m_problem_cluster == nullptr)
//     {
//         return -9;
//     }

//     if(!this->m_problem_cluster->IsInitialized())
//     {
//         return -10;
//     }


//     for(std::size_t i=0; i<this->m_parameters.size(); i++)
//     {
//         if(this->m_parameters[i]->IsInitialized()!=1)
//         {
//             return -8;
//         }
//     }    
    

//     return 1;
// }

// int ClProblem::Create(STATE_CHAIN_POINTER p_state_chain, std::vector<OPERATOR_POINTER>& p_possible_operators, PROBLEM_SOLUTION_DISTANCE_FUNCTION_POINTER p_solution_distance_function, PROBLEM_STORE_POINTER p_previously_tried_hypotheses, PROBLEM_POINTER p_parent_problem, PROBLEM_POINTER& po_problem_instance)
// {
//     return ClProblem::Create(p_state_chain, p_possible_operators, p_solution_distance_function, p_previously_tried_hypotheses, p_parent_problem.get(), po_problem_instance);
// }

int ClProblem::Create(STATE_CHAIN_POINTER p_state_chain, std::vector<OPERATOR_POINTER>& p_possible_operators, PROBLEM_SOLUTION_DISTANCE_FUNCTION_POINTER p_solution_distance_function, std::shared_ptr<Mori::ClCedrusLibani> p_hypotheses_tree, PROBLEM_POINTER p_parent_problem, PROBLEM_POINTER& po_problem_instance)
{
    int result = 0;

    if(p_state_chain == nullptr || p_state_chain->m_blocks.size() == 0 || p_state_chain->m_blocks.back().m_state == nullptr)
    {
        return -1;
    }

    for(std::size_t i=0; i<p_possible_operators.size(); i++)
    {
        if(p_possible_operators[i]==nullptr)
        {
            return -2;
        }
    }

    if(p_hypotheses_tree == nullptr)
    {
        return -3;
    }

    po_problem_instance = std::make_shared<ClProblem>();
    //po_problem_instance->m_previously_tried_hypotheses = p_previously_tried_hypotheses;
    po_problem_instance->m_parent_problem = p_parent_problem;
    //po_problem_instance->m_problematic_state = p_current_state;
    //po_problem_instance->m_wanted_state = p_wanted_state;
    po_problem_instance->m_state_chain = p_state_chain;
    po_problem_instance->m_solution_distance_function = p_solution_distance_function;
    po_problem_instance->m_possible_operators = p_possible_operators;

    /*
    *    Create a new hypothetical solution state
    */
    STATE_POINTER& last_known_state = p_state_chain->m_blocks.back().m_state;
    STATE_POINTER new_hypothesis_state = nullptr;
    
    result = ClState::Create(last_known_state->m_state_variables.size(),new_hypothesis_state);
    if(result != 1)
    {
        return -4;
    }

    new_hypothesis_state->m_state_variables = last_known_state->m_state_variables;
    po_problem_instance->m_hypothetical_solution_state = new_hypothesis_state;
    
    po_problem_instance->m_hypotheses_tree = p_hypotheses_tree;
    po_problem_instance->m_current_hypothesis_tree_node = po_problem_instance->m_hypotheses_tree->GetFirstNode();

    





    return 1;    
}

bool ClProblem::IsInitialized()
{
    return this->m_state_chain != nullptr && this->m_state_chain->m_blocks.size() > 0 && this->m_state_chain->m_blocks.back().m_state != nullptr && this->m_hypotheses_tree != nullptr;
}


// int ClProblem::DefaultIsSolvedFunction(ClOperator* p_operator_to_apply)
// {
//     /*
//     *    Dude, do your job !
//     */
//     return -1;
// }


// int ClProblem::CreateAndCloneTo(PROBLEM_POINTER& po_target_problem)
// {
//     if(this->IsInitialized()!=1)
//     {
//         return -1;
//     }
    
//     PROBLEM_POINTER new_problem = nullptr;
//     int result = ClProblem::CreateProblem(this->m_problematic_state,this->m_possible_operators, this->m_parameters, this->m_is_solved_function_pointer, this->m_problem_cluster, this->m_parent_problem, new_problem);

//     if(result != 1)
//     {
//         return -2;
//     }

//     po_target_problem = new_problem;

//     return 1;
// }

// int ClProblem::NaiveCloneFrom(ClProblem* p_source_problem)
// {
//     int result = 0;

//     this->m_problem_cluster = p_source_problem->m_problem_cluster;
//     this->m_parent_problem = p_source_problem->m_parent_problem;

//     result = ClWorkingMemory::CreateWorkingMemory(this->m_hypothetical_solution_state);
//     if(result != 1)
//     {
//         return -4;
//     }

//     if(this->m_hypothetical_solution_state->CloneFrom(p_source_problem->m_hypothetical_solution_state)!=1)
//     {
//         return -5;
//     }


//     result = ClWorkingMemory::CreateWorkingMemory(this->m_problematic_state);
//     if(result != 1)
//     {
//         return -6;
//     }

//     if(this->m_problematic_state->CloneFrom(p_source_problem->m_problematic_state)!=1)
//     {
//         return -7;
//     }

//     this->m_possible_operators.clear();

//     for(std::size_t i=0; i<p_source_problem->m_possible_operators.size(); i++)
//     {
//         OPERATOR_POINTER new_operator = nullptr;
//         if(ClOperator::CreateOperator(new_operator)!=1)
//         {
//             return -9;
//         }

//         if(new_operator->CloneFrom(p_source_problem->m_possible_operators[i])!=1)
//         {
//             return -10;
//         }

//         this->m_possible_operators.push_back(new_operator);

//         if(p_source_problem->m_chosen_operator == p_source_problem->m_possible_operators[i])
//         {
//             this->m_chosen_operator = new_operator;
//         }
//     }


//     /*
//     *    Clone our parameters
//     */
//     this->m_parameters.clear();
//     for(std::size_t i=0; i<p_source_problem->m_parameters.size(); i++)
//     {
//         VARIABLE_POINTER new_parameter = nullptr;
//         if(ClVariable::CreateVariable(new_parameter)!=1)
//         {
//             return -11;
//         }

//         if(new_parameter->CloneFrom(p_source_problem->m_parameters[i])!=1)
//         {
//             return -12;
//         }

//         this->m_parameters.push_back(new_parameter);
//     }    

    

//     return 1;    
// }

int ClProblem::IsEqualTo(PROBLEM_POINTER p_source_problem)
{
    return this->IsEqualTo(p_source_problem.get());
}

int ClProblem::IsEqualTo(ClProblem* p_source_problem)
{
    return this->GetUID() == p_source_problem->GetUID();
}


int ClProblem::ProposeOperatorToGetCloserToSolution(OPERATOR_POINTER& po_proposed_operator, std::size_t p_number_of_steps_to_foresee)
{
    int result = 0;

    // if(this->IsSolved()==1)
    // {
    //     return 1;
    // }

    std::vector<OPERATOR_POINTER> usable_operators;
    result = this->GetUsableOperators(this->m_possible_operators, usable_operators);
    if(result!=1)
    {
        std::cout << "[ClProblem::ProposeSolution][Problem " << this->GetUID() <<"] Error running [ClState::GetUsableOperators] with result [" << result << "]. (Press any key once you checked it out)" << std::endl;
        std::string nothing;
        std::cin >> nothing;
        return -2;            
    } 

    if(usable_operators.size()==0)
    {
        std::cout << "[ClProblem::ProposeSolution][Problem " << this->GetUID() <<"]: No more possible operator, dead-end" << std::endl;
        return -3;            
    }


    std::cout << "[ClProblem::ProposeSolution][Problem " << this->GetUID() <<"]: [" << usable_operators.size() << "] operator(s) detected, creating sub-problem for each one of them" << std::endl;

    for(std::size_t operator_id = 0; operator_id < usable_operators.size(); operator_id++)
    {
        std::cout << "[ClProblem::ProposeSolution][Problem " << this->GetUID() <<"]: Trying operator [" << usable_operators[operator_id]->m_uid << "]" << std::endl;

        /*
        *    Cloning our problem, but with a single operator
        */
        PROBLEM_POINTER new_problem = nullptr;

        result = ClProblem::Create(this->m_state_chain->Clone(), this->m_possible_operators, this->m_solution_distance_function, this->m_hypotheses_tree, this->shared_from_this(), new_problem);
        new_problem->m_chosen_operator = usable_operators[operator_id];

        /*
        *    Check if this problem is already being solved somewhere else
        */
        PROBLEM_POINTER identical_problem = nullptr;
        result = new_problem->AmIBeingSolvedSomewhereElse(identical_problem);
        if(result < 0)
        {
            std::cout << "    [ClProblem::SolveUsingSpecifiedOperator] : [AmIBeingSolvedSomewhereElse] returned an error of [" << result << "]" << std::endl;    
            return -4;
        }

        if(result == 1)
        {
            std::cout << "    [ClProblem::SolveUsingSpecifiedOperator][Problem " << this->GetUID() <<"]: Is already being computer by Problem [" << identical_problem->GetUID() << "], exiting" << std::endl;
            continue;
        }

        //this->m_previously_tried_hypotheses->m_problems.push_back(new_problem);

        if(new_problem->SolveUsingSpecifiedOperator(usable_operators[operator_id])==1)
        {
            return 1;
        }
    }        
 


    std::cout << "[ClProblem::ProposeSolution][Problem " << this->m_parent_problem <<"]: Tryed all operator(s), nothing worked : dead-end" << std::endl;
    return -5;

    return 1;
}

int ClProblem::SolveUsingSpecifiedOperator(OPERATOR_POINTER p_possible_operator_position_to_apply)
{
    int result = 0;

    std::cout << "    [ClProblem::SolveUsingSpecifiedOperator][Problem " << this->GetUID() <<"] will now try to apply 1 single operator [" << p_possible_operator_position_to_apply->m_uid << "]" << std::endl;

    result = this->ApplyOperator(this->m_chosen_operator);
    if(result!=1)
    {
        std::cout << "    [ClProblem::SolveUsingSpecifiedOperator][Problem " << this->GetUID() <<"]: Could not apply the only available operator, nothing worked : dead-end" << std::endl;
        return -3;                 
    }

    /*
    *    Check if the operator give the result we want
    */
    result = this->IsSolved();
    if(result==1)
    {
        /*
        *    Congrats, problem solved :)
        */
        std::cout << "    [ClProblem::SolveUsingSpecifiedOperator][Problem " << this->GetUID() <<"]: Sucessfully solved problem" << std::endl;        
        return 1;          
    }

    std::cout << "    [ClProblem::SolveUsingSpecifiedOperator] : [ClProblem::IsSolved] returned [" << result << "]" << std::endl;
    return -6;
}




int ClProblem::IsOperatorUsable(OPERATOR_POINTER p_operator)
{
    return 1;

    // if(this->IsInitialized()!=1)
    // {
    //     return -1;
    // }

    // if(p_operator == nullptr)
    // {
    //     return -2;
    // }

    // if(p_operator->IsInitialized()!=1)
    // {
    //     return -3;
    // }

    // if(p_operator->m_pre_selection_conditions == nullptr)
    // {
    //     return 1;
    // }

    // int result = 0;



    // CONDITIONAL_STATEMENT_CONTEXT_POINTER context = nullptr;
    // result = ClConditionalStatementContext::CreateConditionalStatementContext(context);
    // if(result != 1)
    // {
    //     std::cout << "[ClProblem::IsOperatorUsable] Error running [ClConditionalStatementContext::CreateConditionalStatementContext] with result [" << result << "]" << std::endl;
    //     return -4;        
    // } 

    // context->m_data = this;    

    // bool evaluation_result = false;
    // result =  p_operator->m_pre_selection_conditions->EvaluateStatement(context,evaluation_result);
    // if(result != 1)
    // {
    //     std::cout << "[ClProblem::IsOperatorUsable] Error running [ClConditionalStatement::EvaluateStatement] with result [" << result << "]" << std::endl;
    //     return -5;        
    // }    


    // std::string evaluation_string;
    // ClConditionalStatement::GetStatementString(p_operator->m_pre_selection_conditions,evaluation_string);
    // std::cout << "Evaluation string is [" <<  evaluation_string << "]" << std::endl;
    // if(evaluation_result)
    // {
    //     std::cout << "Evaluation result is [TRUE]" << std::endl;
    // }
    // else
    // {
    //     std::cout << "Evaluation result is [FALSE]" << std::endl;
    // }
    

    // if(!evaluation_result)
    // {
    //     return 0;
    // }

    // return 1;
}



int ClProblem::GetUsableOperators(std::vector<OPERATOR_POINTER>& p_possible_operators, std::vector<OPERATOR_POINTER>& po_usable_operators)
{
    if(p_possible_operators.size()==0)
    {
        return -1;
    }  

    po_usable_operators.clear();

    int result = 0;
    for(std::size_t i=0; i<p_possible_operators.size(); i++)
    {
        if(p_possible_operators[i] == nullptr)
        {
            return -2;
        }

        result = this->IsOperatorUsable(p_possible_operators[i]);
        if(result==1)
        {
            po_usable_operators.push_back(p_possible_operators[i]);
        }
    } 

    return 1;
}



int ClProblem::ApplyOperator(OPERATOR_POINTER p_operator)
{
    if(p_operator == nullptr)
    {
        return -1;
    }

    std::cout << "[ClProblem::ApplyOperator] Applying operator [" << p_operator->m_uid << "] on problem [" << this->GetUID() << "]" << std::endl;

    int result = p_operator->Execute(this);
    if(result != 1)
    {
        std::cout << "[ClProblem::ApplyOperator] Apply function returned [" << result << "]" << std::endl;
        return -2;
    }

    return 1;
}

int ClProblem::IsSolved()
{
    if(this->m_hypothetical_solution_state == nullptr)
    {
        return -1;
    }

    return this->m_solution_distance_function(this,this->m_hypothetical_solution_state) <=  0.05;
}



int ClProblem::AmIBeingSolvedSomewhereElse(PROBLEM_POINTER& po_identical_problem)
{
    for(std::size_t i=0; i<this->m_previously_tried_hypotheses->m_problems.size(); i++)
    {
        if(this->m_previously_tried_hypotheses->m_problems.at(i).get() == this)
        {
            continue;
        } 

        int result = this->IsEqualTo(this->m_previously_tried_hypotheses->m_problems.at(i));
        if(result == 1)
        {
            po_identical_problem = this->m_previously_tried_hypotheses->m_problems.at(i);
            return 1;
        }
    }

    return 0;
}