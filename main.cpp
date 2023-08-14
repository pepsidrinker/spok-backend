#include "Include/ClState.hpp"
#include "Include/ClOperator.hpp"
#include "Include/ClProblem.hpp"
#include "Include/ClStateChain.hpp"
#include "Include/ClCausalInferer.hpp"
#include "Include/ClMatrix.hpp"

#include <string>
#include <sstream>
#include <iostream>

STATE_POINTER g_initial_state = nullptr;
STATE_CHAIN_POINTER g_states_chain = nullptr;

const std::size_t g_number_of_variables_per_state = 3;


int operator_touch(STATE_POINTER& p_source_state, STATE_POINTER& po_destination_pointer)
{
    return 1;
}

int main()
{
    std::cout << "Initializing...please wait" << std::endl;

    int result = 0;

    result = ClState::Create(g_number_of_variables_per_state,g_initial_state);
    if(result != 1)
    {
        std::cout << "Error running [ClState::Create] with result [" << result << "]" << std::endl;
        return -1;
    }

    result = ClStateChain::Create(g_states_chain);
    if(result != 1)
    {
        std::cout << "Error running [ClStateChain::Create] with result [" << result << "]" << std::endl;
        return -2;
    }


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

        for(std::size_t variable_index = 0; variable_index < g_number_of_variables_per_state; variable_index++)
        {
            std::cout << "Please input the value of variable [" << variable_index << "]" << std::endl;
            std::string user_input;
            std::cin >> user_input;
            std::stringstream ss;
            int integer_user_input = 0;
            ss >> integer_user_input;

            new_timestep_state->m_state_variables[variable_index] = integer_user_input;
        }

        std::cout << "State for timestep [" << g_current_timestep << "]" << std::endl;
        new_timestep_state->Print();
        std::cout << "Press any key to run [association] on the current step" << std::endl;
        std::string rien;
        std::cin >> rien;
        

    }





    

    return 0;
}


//step 1 : make a model of the world through association , then intervention, then conterfactuals
//step 2 : defined the ultimate goal
//step 3 : sub/problem solving loop