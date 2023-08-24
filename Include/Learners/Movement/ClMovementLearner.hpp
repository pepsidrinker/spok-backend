#pragma once

#include "../ClLearner.hpp"
#include "ClMovement.hpp"


class ClMovementLearner : public ClLearner
{
    private:
        int ComputeMovements(STATE_POINTER p_previous_timestep_state, std::shared_ptr<std::vector<ClMovement>>& p_previous_timestep_state_ClMovements, STATE_POINTER p_next_timestep_state, std::shared_ptr<std::vector<ClMovement>>& po_new_transition_ClMovements);

    public:
        virtual ~ClMovementLearner();
        int GetTransition(ClStateChain* p_state_chain, CUSTOM_TRANSITION_DATA_POINTER& po_new_transition_data);
        void Print(CUSTOM_TRANSITION_DATA_POINTER p_transition_data) override;

        // int Predict(STATE_CHAIN_POINTER p_state_chain, float& po_predicted_value);
        // int Learn(STATE_CHAIN_POINTER p_state_chain, float p_predicted_value, float p_actual_value);
};