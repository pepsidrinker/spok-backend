#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include <cmath>

#include "ClState.hpp"
//#include "Learners/ClLearner.hpp"
#include <memory>

class ClLearner;

class ClStateTransition
{
    public:
        struct LEARNER_TRANSITION_INFORMATIONS
        {
            std::shared_ptr<ClLearner>  m_learner_instance;
            std::shared_ptr<void> m_learner_transition_data;
            std::shared_ptr<ClState> m_next_timestep_predictive_state;

            LEARNER_TRANSITION_INFORMATIONS()
            {
                this->m_learner_instance = nullptr;
                this->m_learner_transition_data = nullptr;
                this->m_next_timestep_predictive_state = nullptr;
            }
        };    

        std::vector<LEARNER_TRANSITION_INFORMATIONS> m_learners_transitions;

        ClStateTransition();
        ~ClStateTransition();
        static int Create(std::size_t p_number_of_variable, std::shared_ptr<ClStateTransition>& po_new_state_transition);
        //int GetLearnerTransitionDataByLearnerType(unsigned short p_learner_type, LEARNER_TRANSITION_INFORMATIONS& po_learner_transition_informations);
        //void Print();
};

typedef std::shared_ptr<void> CUSTOM_TRANSITION_DATA_POINTER;
typedef std::shared_ptr<ClStateTransition> STATE_TRANSITION_POINTER;