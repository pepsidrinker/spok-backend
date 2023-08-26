#pragma once

class ClMovement
{
    public:
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
        float m_velocity;

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
        float m_acceleration;

        ClMovement()
        {
            this->m_velocity = 0.00;
            this->m_acceleration = 0.00;
        };

        bool operator==(const ClMovement& p_other) const
        {
            return (this->m_velocity == p_other.m_velocity) && (this->m_acceleration == p_other.m_acceleration);
        }

        bool operator!=(const ClMovement& p_other) const
        {
            return !(*this == p_other);
        }
};