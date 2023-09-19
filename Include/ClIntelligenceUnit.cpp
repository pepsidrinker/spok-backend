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

    result = ClProblemStore::Create(po_intelligence_unit_instance->m_problem_store);
    if(result != 1)
    {
        std::cout << "Error running [ClProblemStore::Create] with result [" << result << "]" << std::endl;
        return -5;        
    }    

    result = ClMovementLearner::Create(po_intelligence_unit_instance->m_movement_learner);
    if(result != 1)
    {
        std::cout << "Error running [ClMovementLearner::Create] with result [" << result << "]" << std::endl;
        return -6;        
    }

    po_intelligence_unit_instance->m_possible_operators = p_possible_operators;
    po_intelligence_unit_instance->m_solution_distance_function = p_solution_distance_function;
    po_intelligence_unit_instance->m_problem = nullptr;




    return 1;
}

bool ClIntelligenceUnit::IsInitialized()
{
    return (this->m_state_chain != nullptr && this->m_problem_store != nullptr && this->m_problem != nullptr);
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

    ClStateTransition::LEARNER_TRANSITION_INFORMATIONS movement_learner_transition_informations;

    movement_learner_transition_informations.m_learner_instance = this->m_movement_learner;

    result = this->m_movement_learner->AddTimestep(p_state->m_state_variables,movement_learner_transition_informations.m_learner_transition_data);
    if(result != 1)
    {
        return -3;
    }

    result = ClState::Create(p_state->m_state_variables.size(), movement_learner_transition_informations.m_next_timestep_predictive_state);
    if(result != 1)
    {
        return -4;
    }


    result = this->m_movement_learner->PredictNextStateVariables(movement_learner_transition_informations.m_next_timestep_predictive_state->m_state_variables,1);
    if(result != 1)
    {
        return -5;
    }

    new_block.m_transition->m_learners_transitions.push_back(movement_learner_transition_informations);
    new_block.m_predictive_next_state = movement_learner_transition_informations.m_next_timestep_predictive_state;

    this->m_state_chain->m_blocks.push_back(new_block);

    return 1;
}

int ClIntelligenceUnit::AddNewTimestep(STATE_POINTER& p_state)
{
    if(this->m_state_chain == nullptr || this->m_problem_store == nullptr)
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

    result = this->AddNewBlockToStateChain(p_state);
    if(result != 1)
    {
        std::cout << "[ClIntelligenceUnit::AddNewTimestep] Error running [ClIntelligenceUnit::AddNewBlockToStateChain] with result [" << result << "]" << std::endl;        
        return -3;
    }

    /*
    *    Make sure ww have at least 1 state in our chain to create our problem
    */
    if(this->m_problem == nullptr)
    {
        result = ClProblem::Create(this->m_state_chain,this->m_possible_operators,this->m_solution_distance_function,this->m_problem_store,nullptr,this->m_problem);
        if(result != 1)
        {
            std::cout << "[ClIntelligenceUnit::AddNewTimestep] Error running [ClProblem::Create] with result [" << result << "]" << std::endl;        
            return -4;
        }

        std::cout << "[ClIntelligenceUnit::AddNewTimestep] Problem successfully created" << std::endl;
    }
    
    return 1;

}

int ClIntelligenceUnit::ProposeSolution(STATE_CHAIN_POINTER& po_solution_state_chain)
{
    if(!this->IsInitialized())
    {
        std::cout << "[ClIntelligenceUnit::ProposeSolution] Instance not fully initialized" << std::endl;        
        return -1;
    }

    PROBLEM_POINTER proposed_solution = nullptr;
    int result = this->m_problem->ProposeSolution(proposed_solution);
    if(result != 1)
    {
        std::cout << "[ClIntelligenceUnit::ProposeSolution] Error running [ClProblem::ProposeSolution] with result [" << result << "]" << std::endl;        
        return -2;
    }

    return 1;
}