#include "ClProblem.hpp"

ClProblem::ClProblem()
{
    this->m_state_chain = nullptr;
    this->m_solution_distance_function = nullptr;
    this->m_parent_problem = nullptr;
    this->m_hypothetical_solution_distance = std::numeric_limits<float>::max();
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

    return result;
}


int ClProblem::Create(STATE_CHAIN_POINTER p_state_chain, std::vector<OPERATOR_POINTER>& p_possible_operators, PROBLEM_SOLUTION_DISTANCE_FUNCTION_POINTER p_solution_distance_function, HYPOTHESIS_STORE_POINTER p_hypotheses_store, PREDICTOR_POINTER p_predictor, PROBLEM_POINTER p_parent_problem, PROBLEM_POINTER& po_problem_instance)
{
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

    if(p_hypotheses_store == nullptr)
    {
        return -3;
    }

    if(p_predictor == nullptr)
    {
        return -4;
    }

    po_problem_instance = std::make_shared<ClProblem>();
    po_problem_instance->m_parent_problem = p_parent_problem;
    po_problem_instance->m_state_chain = p_state_chain;
    po_problem_instance->m_solution_distance_function = p_solution_distance_function;
    po_problem_instance->m_possible_operators = p_possible_operators;
    po_problem_instance->m_predictor = p_predictor;
    po_problem_instance->m_global_hypothesis_store = p_hypotheses_store;

    return 1;    
}

bool ClProblem::IsInitialized()
{
    return this->m_state_chain != nullptr && this->m_state_chain->m_blocks.size() > 0 && this->m_state_chain->m_blocks.back().m_state != nullptr && this->m_predictor != nullptr;;
}

int ClProblem::IsEqualTo(PROBLEM_POINTER p_source_problem)
{
    return this->IsEqualTo(p_source_problem.get());
}

int ClProblem::IsEqualTo(ClProblem* p_source_problem)
{
    return this->GetUID() == p_source_problem->GetUID();
}

int ClProblem::HasHypothesisBeenTriedBefore(ClHypothesis& p_hypothesis)
{
    for(std::size_t i=0; i<this->m_global_hypothesis_store->m_hypotheses.size(); i++)
    {
        if(p_hypothesis.GetUID() == this->m_global_hypothesis_store->m_hypotheses[i].GetUID())
        {
            return 1;
        }
    }
    return 0;
}

int ClProblem::ProposeOperatorToGetCloserToSolution(OPERATOR_POINTER& po_proposed_operator, std::size_t p_number_of_steps_to_foresee)
{
    int result = 0;


    /*
    *    Check if you new state solves our problem
    */
    STATE_POINTER current_state = this->m_state_chain->m_blocks.back().m_state;
    if(this->m_solution_distance_function(this,current_state) == 0.00)
    {
        std::cout << "[ClProblem::ProposeOperatorToGetCloserToSolution][Problem " << this->GetUID() <<"]: Problem already solved with current state" << std::endl;
        return 1;
    }


    /*
    *    Create an hypothesis for every possible operator
    */
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


    std::cout << "[ClProblem::ProposeSolution][Problem " << this->GetUID() <<"]: [" << usable_operators.size() << "] operator(s) detected, creating a hypothesis for each one of them" << std::endl;

    for(std::size_t operator_id = 0; operator_id < usable_operators.size(); operator_id++)
    {
        ClHypothesis new_hypothesis;
        new_hypothesis.m_operator = usable_operators[operator_id];
        
        result = ClState::Create(this->m_state_chain->m_blocks.back().m_state->m_state_variables.size(), new_hypothesis.m_predictive_state);
        if(result!=1)
        {
            std::cout << "[ClProblem::ProposeSolution][Problem " << this->GetUID() <<"] Error running [ClState::Create] for new hypothesis with result [" << result << "]" << std::endl;
            return -4;            
        }
        
        /*
        *    Check if this hypothesis has already been tried before
        */
        if(this->HasHypothesisBeenTriedBefore(new_hypothesis) == 1)
        {
            std::cout << "[ClProblem::ProposeSolution][Problem " << this->GetUID() <<"]: Hypothesis [" << new_hypothesis.GetUID() << "] has already been tried before, skipping it" << std::endl;
            continue;
        }

        this->m_hypotheses.push_back(new_hypothesis);
    } 

    if(this->m_hypotheses.size()==0)
    {
        std::cout << "[ClProblem::ProposeSolution][Problem " << this->GetUID() <<"]: No more possible hypothesis, dead-end" << std::endl;
        return -5;            
    }

    result = this->ComputeHypothesesPredictiveState();
    if(result!=1)
    {
        std::cout << "[ClProblem::ProposeSolution][Problem " << this->GetUID() <<"] Error running [ClProblem::ComputeHypothesesPredictiveState] with result [" << result << "]" << std::endl;
        return -6;            
    }

    std::vector<std::size_t> hypotheses_indexes_that_solved_problem;
    result = this->GetHypothesesIndexesThatSolvedProblem(hypotheses_indexes_that_solved_problem);       
    if(hypotheses_indexes_that_solved_problem.size() > 0)
    {
        std::cout << "[ClProblem::ProposeSolution][Problem " << this->GetUID() <<"]: [" << hypotheses_indexes_that_solved_problem.size() << "] some hypothesis(es) solved the problem" << std::endl;
        return 1;
    }
 
    std::cout << "[ClProblem::ProposeSolution][Problem " << this->m_parent_problem <<"]: Tryed all hypotheses for this timestep, nothing worked : dead-end" << std::endl;
    return 0;
}


int ClProblem::ComputeHypothesesPredictiveState()
{
    for(std::size_t i=0; i<this->m_hypotheses.size(); i++)
    {
        std::cout << "[ClProblem::ComputeHypothesesPredictiveState][Problem " << this->GetUID() <<"]: Running operator [" << this->m_hypotheses[i].m_operator->m_uid << "]" << std::endl;
        int result = this->m_hypotheses[i].m_operator->Execute(this, this->m_hypotheses[i].m_predictive_state);
        if(result!=1)
        {
            std::cout << "[ClProblem::ComputeHypothesesPredictiveState][Problem " << this->GetUID() <<"] Error running [ClOperator::Execute] with result [" << result << "]" << std::endl;
            return -1;            
        }
    }


    return 1;
}


int ClProblem::GetHypothesesIndexesThatSolvedProblem(std::vector<std::size_t>& po_solved_hypotheses_indexes)
{
    po_solved_hypotheses_indexes.clear();
    for(std::size_t i=0; i<this->m_hypotheses.size(); i++)
    {
        if(this->m_solution_distance_function(this,this->m_hypotheses[i].m_predictive_state) == 0.00)
        {
            po_solved_hypotheses_indexes.push_back(i);
        }
    }


    return 1;
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


