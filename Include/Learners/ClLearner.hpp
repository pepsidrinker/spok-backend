#pragma once


#include <memory>
#include <vector>


class ClLearner
{
    public:
        const unsigned short LEARNER_TYPE = 0;
        virtual int AddTimestep(std::vector<float>& p_current_timestep_variables, std::shared_ptr<void>& po_new_transition_data) = 0;
        virtual int PredictNextStateVariables(std::vector<float>& po_next_timestep, std::size_t p_number_of_timestep_in_the_future) = 0;
        virtual ~ClLearner();
        virtual void Print(std::shared_ptr<void> p_transition_data) = 0;
};

typedef std::shared_ptr<ClLearner> LEARNER_POINTER;