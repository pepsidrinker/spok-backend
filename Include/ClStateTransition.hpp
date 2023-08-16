#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include <cmath>

#include "ClState.hpp"

class ClStateTransition
{
    public:
    struct MOVEMENT
    {
        /*
        *    Velocity:
        *    Velocity refers to the rate of change of an object's position with respect to time. 
        *    It is a vector quantity, meaning it has both magnitude (speed) and direction. 
        *    In mathematical terms, velocity is defined as the derivative of position with respect to time.
        *
        *    Formula: Velocity (v) = Change in Position (Δx) / Change in Time (Δt)
        *
        *    Velocity is what tells you not only how fast an object is moving but also in which direction it is moving. 
        *    For example, a car traveling at 60 miles per hour to the north has a velocity of 60 mph in the north direction.
        */
        float m_velocity_speed;
        float m_velocity_direction_x;
        float m_velocity_direction_y;

        /*
        *    Acceleration:
        *    Acceleration refers to the rate of change of an object's velocity with respect to time. 
        *    Like velocity, it is also a vector quantity. 
        *    Acceleration can occur when an object changes its speed, direction, or both.
        *
        *    Formula: Acceleration (a) = Change in Velocity (Δv) / Change in Time (Δt)
        *
        *    Acceleration indicates how quickly an object's velocity is changing. 
        *    If an object is speeding up, slowing down, or changing direction, it is experiencing acceleration. 
        *    For example, a car accelerating from 0 to 60 miles per hour in 10 seconds is experiencing acceleration.
        *
        *    In summary, velocity focuses on an object's speed and direction of motion, while acceleration focuses on changes in an object's velocity. 
        *    Both velocity and acceleration are vector quantities, meaning they have both numerical values and directions.
        */
        float m_acceleration_speed;
        float m_accelration_direction_x;
        float m_accelration_direction_y;

        MOVEMENT()
        {
            this->m_velocity_speed = 0.00;
            this->m_velocity_direction_x = 0.00;
            this->m_velocity_direction_y = 0.00;
            this->m_acceleration_speed = 0.00;
            this->m_accelration_direction_x = 0.00;
            this->m_accelration_direction_y = 0.00;
        };

        bool operator==(const MOVEMENT& p_other) const
        {
            return (m_velocity_speed == p_other.m_velocity_speed) &&
                (m_velocity_direction_x == p_other.m_velocity_direction_x) &&
                (m_velocity_direction_y == p_other.m_velocity_direction_y) &&
                (m_acceleration_speed == p_other.m_acceleration_speed) &&
                (m_accelration_direction_x == p_other.m_accelration_direction_x) &&
                (m_accelration_direction_y == p_other.m_accelration_direction_y);
        }

        bool operator!=(const MOVEMENT& p_other) const
        {
            return !(*this == p_other);
        }
    };

    std::vector<MOVEMENT> m_state_variables_transitions;

    ClStateTransition();
    ~ClStateTransition();
    static int Create(std::size_t p_number_of_variable, std::shared_ptr<ClStateTransition>& po_new_state_transition);
    static int Compute(STATE_POINTER p_previous_timestep_state, std::shared_ptr<ClStateTransition> p_previous_timestep_state_transition, STATE_POINTER p_next_timestep_state, std::shared_ptr<ClStateTransition>& po_new_transition_pointer);
    void Print();
};

typedef std::shared_ptr<ClStateTransition> STATE_TRANSITION_POINTER;