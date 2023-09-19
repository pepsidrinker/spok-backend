#pragma once

#include "ClState.hpp"
#include "ClStateChain.hpp"

#include "Learners/Movement/ClMovementLearner.hpp"

#include <memory>


class ClPredictor
{
    protected:
        STATE_CHAIN_POINTER m_state_chain;
        std::size_t m_last_processed_state_chain_block_index;
        MOVEMENT_LEARNER_POINTER m_movement_learner;

    public:
        ClPredictor();
        ~ClPredictor();

        static int Create(STATE_CHAIN_POINTER p_state_chain, std::shared_ptr<ClPredictor>& po_new_instance);
        int ProcessUpdatesFromStateChain();
        int PredictNextState(STATE_POINTER& po_next_state, std::size_t p_number_of_timestep_in_the_future);
};

typedef std::shared_ptr<ClPredictor> PREDICTOR_POINTER;