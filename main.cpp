#include "Include/ClState.hpp"
#include "Include/ClOperator.hpp"
#include "Include/ClProblem.hpp"
#include "Include/ClStateChain.hpp"
//#include "Include/ClCausalInferer.hpp"
#include "Include/ClMatrix.hpp"

#include "Include/Learners/Movement/ClMovementLearner.hpp"

#include <string>
#include <sstream>
#include <iostream>

STATE_POINTER g_initial_state = nullptr;
STATE_CHAIN_POINTER g_states_chain = nullptr;

const std::size_t g_number_of_variables_per_state = 1;


// int operator_touch(STATE_POINTER& p_source_state, STATE_POINTER& po_destination_pointer)
// {
//     return 1;
// }


float GetVariableNextTimestep()
{
    static float last_position = 0.00;
    
    float added_value = 2.0;

    if(last_position >= 10)
    {
        added_value=1;
    }

    last_position += added_value;

    if(last_position >= 20)
    {
        last_position = 0;
    }

    return last_position;
}

int main()
{
    std::cout << "Initializing...please wait" << std::endl;

    int result = 0;

    result = ClStateChain::Create(g_states_chain);
    if(result != 1)
    {
        std::cout << "Error running [ClStateChain::Create] with result [" << result << "]" << std::endl;
        return -1;
    }


    /*
    *    Instanciate our learners
    */
    MOVEMENT_LEARNER_POINTER movement_learner = nullptr;
    result = ClMovementLearner::Create(movement_learner);
    if(result != 1)
    {
        std::cout << "Error running [ClMovementLearner::Create with result [" << result << "]" << std::endl;
        return -2;        
    }

    g_states_chain->m_learner_instances.push_back(movement_learner);


    


    std::cout << "Populating initial state..." << std::endl;


    std::size_t g_current_timestep = 0;
    while(1)
    {
        STATE_POINTER new_timestep_state = nullptr;
        if(ClState::Create(g_number_of_variables_per_state,new_timestep_state)!=1)
        {
            std::cout << "Error running [ClStateChain::Create] with result [" << result << "]" << std::endl;
            return -3;            
        }

        float state_variable;
        state_variable = GetVariableNextTimestep();
        new_timestep_state->m_state_variables[0] = state_variable;

        g_states_chain->AddState(new_timestep_state);
        float predicted_position;
        if(g_states_chain->m_blocks.back().m_predictive_next_state != nullptr)
        {
            predicted_position = g_states_chain->m_blocks.back().m_predictive_next_state->m_state_variables[0];
        }

        std::cout << "Current position [" << state_variable << "],  predicted next position [" << predicted_position << "]" << std::endl;

        // std::cout << "Latest block of global state chain for timestep [" << g_current_timestep << "]" << std::endl;
        // g_states_chain->Print();
        std::cout << "Press any key to keep running" << std::endl;
        std::cout << "==================================================" << std::endl;

        std::cout << std::endl << std::endl << std::endl;

        std::string rien;
        std::cin >> rien;
    }





    

    return 0;
}


//step 1 : make a model of the world through association , then intervention, then conterfactuals
//step 2 : defined the ultimate goal
//step 3 : sub/problem solving loop