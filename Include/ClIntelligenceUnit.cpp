#include "ClIntelligenceUnit.hpp"


ClIntelligenceUnit::ClIntelligenceUnit(){}
ClIntelligenceUnit::~ClIntelligenceUnit(){}

int ClIntelligenceUnit::Create(std::vector<OPERATOR_POINTER>& p_possible_operators, ClProblem::PROBLEM_SOLUTION_DISTANCE_FUNCTION_POINTER p_solution_distance_function, INTELLIGENCE_UNIT_POINTER& po_intelligence_unit_instance)
{
    if(p_possible_operators.size() == 0)
    {
        return -2;
    }

    if(p_solution_distance_function == nullptr)
    {
        return -3;
    }

    int result = 0;

    po_intelligence_unit_instance = std::make_shared<ClIntelligenceUnit>();    

    result = ClStateChain::Create(po_intelligence_unit_instance->m_state_chain);
    if(result != 1)
    {
        std::cout << "[ClIntelligenceUnit::Create] Error running [ClStateChain::Create] with result [" << result << "]" << std::endl;
        return -4;
    }

    result = ClPredictor::Create(po_intelligence_unit_instance->m_state_chain, po_intelligence_unit_instance->m_predictor);
    if(result != 1)
    {
        std::cout << "[ClIntelligenceUnit::Create] Error running [ClPredictor::Create] with result [" << result << "]" << std::endl;
        return -5;
    } 

    po_intelligence_unit_instance->m_possible_operators = p_possible_operators;
    po_intelligence_unit_instance->m_solution_distance_function = p_solution_distance_function;
    po_intelligence_unit_instance->m_problem = nullptr;




    return 1;
}

bool ClIntelligenceUnit::IsInitialized()
{
    return (this->m_state_chain != nullptr && this->m_predictor != nullptr && this->m_problem != nullptr && this->m_solution_distance_function != nullptr);
}


int ClIntelligenceUnit::AddNewBlockToStateChain(STATE_POINTER& p_state)
{
    ClStateChain::STATE_CHAIN_BLOCK new_block;
    new_block.m_state = p_state;
    new_block.m_transition = nullptr;

    if(this->m_state_chain->m_blocks.size()==0)
    {
        this->m_state_chain->m_blocks.push_back(new_block);
        return 1;
    }

    int result = ClStateTransition::Create(new_block.m_transition);
    if(result != 1)
    {
        return -2;
    }

    this->m_state_chain->m_blocks.push_back(new_block);

    return 1;
}

int ClIntelligenceUnit::AddNewTimestep(STATE_POINTER& p_state)
{
    if(this->m_state_chain == nullptr || this->m_predictor == nullptr)
    {
        std::cout << "[ClIntelligenceUnit::AddNewTimestep] Instance not fully initialized" << std::endl;        
        return -1;
    }

    if(p_state == nullptr)
    {
        std::cout << "[ClIntelligenceUnit::AddNewTimestep] Parameter [p_state] is null" << std::endl;        
        return -2;
    }

    int result = 0;

    /*
    *    Add a new block to our state chain
    */
    result = this->AddNewBlockToStateChain(p_state);
    if(result != 1)
    {
        std::cout << "[ClIntelligenceUnit::AddNewTimestep] Error running [ClIntelligenceUnit::AddNewBlockToStateChain] with result [" << result << "]" << std::endl;        
        return -3;
    }


    /*
    *     Tell our predictor we received a new block in our state chain, so it can process it
    */
    result = this->m_predictor->ProcessUpdatesFromStateChain();
    if(result != 1)
    {
        std::cout << "[ClIntelligenceUnit::AddNewTimestep] Error running [ClPredictor::ProcessUpdatesFromStateChain] with result [" << result << "]" << std::endl;        
        return -4;
    }


    /*
    *    Make sure ww have at least 1 state in our chain to create our problem
    */
    if(this->m_problem == nullptr)
    {
        /*
        *    Create a global hypotheses store for our main problem & it's sub problem
        */
        HYPOTHESIS_STORE_POINTER global_hypothesis_store = nullptr;
        result = ClHypothesisStore::Create(global_hypothesis_store);
        if(result != 1)
        {
            std::cout << "[ClIntelligenceUnit::AddNewTimestep] Error running [ClHypothesisStore::Create] with result [" << result << "]" << std::endl;        
            return -4;
        }             


        result = ClProblem::Create(this->m_state_chain,this->m_possible_operators,this->m_solution_distance_function,global_hypothesis_store,this->m_predictor,nullptr,this->m_problem);
        if(result != 1)
        {
            std::cout << "[ClIntelligenceUnit::AddNewTimestep] Error running [ClProblem::Create] with result [" << result << "]" << std::endl;        
            return -5;
        }

        std::cout << "[ClIntelligenceUnit::AddNewTimestep] Problem successfully created" << std::endl;
    }
    
    return 1;

}

int ClIntelligenceUnit::ProposeOperatorToGetCloserToSolution(OPERATOR_POINTER& po_proposed_operator, std::size_t p_number_of_steps_to_foresee)
{
    if(!this->IsInitialized())
    {
        std::cout << "[ClIntelligenceUnit::ProposeSolution] Instance not fully initialized" << std::endl;        
        return -1;
    }

    OPERATOR_POINTER proposed_operator = nullptr;
    int result = this->m_problem->ProposeOperatorToGetCloserToSolution(proposed_operator, p_number_of_steps_to_foresee);
    if(result != 1)
    {
        std::cout << "[ClIntelligenceUnit::ProposeSolution] Error running [ClProblem::ProposeSolution] with result [" << result << "]" << std::endl;        
        return -2;
    }

    return 1;
}