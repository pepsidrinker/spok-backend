#pragma once

#include "../ClLearner.hpp"
#include "ClMovement.hpp"


#include <vector>
#include <memory>
#include <iostream>



class ClMovementLearner : public ClLearner
{
    private:
        int ComputeMovements(std::vector<float>& p_previous_timestep_variables, std::vector<ClMovement>& p_previous_timestep_variables_movements, std::vector<float>& p_next_timestep_variables, std::vector<ClMovement>& po_new_transition_movements);
        int PredictNextStateVariable(float p_variable_current_value, ClMovement& p_movement, std::size_t p_number_of_timestep_in_the_future, float& po_variable_predicted_value);
        
        std::vector<float> m_previous_timestep_variables;
        std::vector<ClMovement> m_previous_timestep_movements;


    public:
        const unsigned short LEARNER_TYPE = 1;
        virtual ~ClMovementLearner();
        int AddTimestep(std::vector<float>& p_current_timestep_variables, std::shared_ptr<void>& po_new_transition_data) override;
        int PredictNextStateVariables(std::vector<float>& po_next_timestep, std::size_t p_number_of_timestep_in_the_future) override;
        void Print(std::shared_ptr<void> p_transition_data) override;
        static int Create(std::shared_ptr<ClMovementLearner>& po_new_instance);

        // int Learn(STATE_CHAIN_POINTER p_state_chain, float p_predicted_value, float p_actual_value);
};

typedef std::shared_ptr<ClMovementLearner> MOVEMENT_LEARNER_POINTER;