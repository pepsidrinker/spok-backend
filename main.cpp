#include "Include/ClState.hpp"
#include "Include/StateReaders/Memcache/ClMemcacheStateReader.hpp"

#include "Include/ClIntelligenceUnit.hpp"


#include <string>
#include <sstream>
#include <iostream>

STATE_POINTER g_initial_state = nullptr;
STATE_CHAIN_POINTER g_states_chain = nullptr;

const std::size_t g_number_of_variables_per_state = 1;


int operator_wait(void* p_problem_instance, STATE_POINTER p_result_state)
{
    // ClProblem* problem_instance = (ClProblem*)p_problem_instance;
    // problem_instance->m_hypothetical_solution_state = problem_instance->m_state_chain->m_blocks.back().m_state->Clone();
    return 1;
}

// int operator_move_right(void* p_problem_instance)
// {
//     return 1;
// }

float GetDistanceBetweenBallAndCharacter(ClProblem* p_problem, STATE_POINTER p_state_to_evaluate)
{
    float ball_position_y = p_state_to_evaluate->m_state_variables.back();
    float character_position_y = p_state_to_evaluate->m_state_variables[p_state_to_evaluate->m_state_variables.size()-3];
    float distance = std::abs(character_position_y - ball_position_y);
    float error_score = 1.0/(distance+0.000001);
 
    std::cout << "Ball position [" << ball_position_y << "], character position [" << character_position_y << "], distance [" << distance << "], error score [" << error_score << "]" << std::endl;

    return error_score;
}


int main()
{

    std::cout << "Initializing...please wait" << std::endl;

    int result = 0;


    /*
    *    Instanciate our state reader
    */
    MEMCACHE_STATE_READER_POINTER memcache_state_reader = nullptr;
    result = ClMemcacheStateReader::Create(memcache_state_reader);
    if(result != 1)
    {
        std::cout << "Error running [ClMemcacheStateReader::Create] with result [" << result << "]" << std::endl;
        return -1;
    }    


    /*
    *    Prepare all we need to solve our main problem
    */
    OPERATOR_POINTER operator_wait_pointer = nullptr;
    result = ClOperator::Create(operator_wait, operator_wait_pointer);
    if(result != 1)
    {
        std::cout << "Error running [ClOperator::Create] with result [" << result << "]" << std::endl;
        return -2;        
    }

    std::vector<OPERATOR_POINTER> possible_operators;
    possible_operators.push_back(operator_wait_pointer);


    INTELLIGENCE_UNIT_POINTER g_intelligence_unit = nullptr;
    result = ClIntelligenceUnit::Create(possible_operators, GetDistanceBetweenBallAndCharacter, g_intelligence_unit);
    if(result != 1)
    {
        std::cout << "Error running [ClIntelligenceUnit::Create] with result [" << result << "]" << std::endl;
        return -3;        
    }



    /*
    *    Main loop
    */
    std::cout << "Entering main loop" << std::endl;

    while(1)
    {
        STATE_POINTER new_timestep_state = nullptr;
        
        std::cout << "Waiting for new timestep" << std::endl;
        result = memcache_state_reader->WaitForNewState(new_timestep_state);
        if(result != 1)
        {
            std::cout << "Error running [ClMemcacheStateReader::WaitForNewState] with result [" << result << "]" << std::endl;
            return -3;                    
        }
        std::cout << "New timestep arrived" << std::endl;

        result = g_intelligence_unit->AddNewTimestep(new_timestep_state);
        if(result != 1)
        {
            std::cout << "Error running [ClIntelligenceUnit::AddNewTimestep] with result [" << result << "]" << std::endl;
            return -4;                    
        }

        OPERATOR_POINTER proposed_operator = nullptr;
        result = g_intelligence_unit->ProposeOperatorToGetCloserToSolution(proposed_operator, 1);
        if(result != 1)
        {
            std::cout << "Error running [ClIntelligenceUnit::ProposeSolution] with result [" << result << "]" << std::endl;
            return -5;                    
        }

      





        /*
        *   What do we predict for the next state ?
        *   If we notice that letting thing run their course wont get us closer to our goal, 
        *   we can intervene and apply an operator to the current state.
        */


        // float predicted_position;
        // if(g_states_chain->m_blocks.back().m_predictive_next_state != nullptr)
        // {
        //     predicted_position = g_states_chain->m_blocks.back().m_predictive_next_state->m_state_variables.back();
        // }

        //std::cout << "Current ball position [" << new_timestep_state->m_state_variables.back() << "],  predicted next position [" << predicted_position << "], which gives us an error of [" << g_main_problem->GetCurrentStateSolutionDistance() << "]" << std::endl;

        // std::cout << "Latest block of global state chain for timestep [" << g_current_timestep << "]" << std::endl;
        // g_states_chain->Print();
        // std::cout << "Press any key to keep running" << std::endl;
        // std::cout << "==================================================" << std::endl;

        // std::cout << std::endl << std::endl << std::endl;

        // std::string rien;
        // std::cin >> rien;
    }





    

    return 0;
}


//step 1 : make a model of the world through association , then intervention, then conterfactuals
//step 2 : defined the ultimate goal
//step 3 : sub/problem solving loop


