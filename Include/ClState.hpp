#pragma once

#include <memory>
#include <vector>
#include <iostream>

class ClState
{
    public:
    struct POSITION
    {
        float m_x;
        float m_y;

        POSITION()
        {
            this->m_x = 0.00;
            this->m_y = 0.00;
        }

        bool operator==(const POSITION& p_other) const
        {
            return (m_x == p_other.m_x) && (m_y == p_other.m_y);
        }

        bool operator!=(const POSITION& p_other) const
        {
            return !(*this == p_other);
        }
    };
    std::vector<POSITION> m_state_variables;

    ClState();
    ~ClState();
    static int Create(std::size_t p_number_of_variable, std::shared_ptr<ClState>& po_new_state);
    void Print();
};

typedef std::shared_ptr<ClState> STATE_POINTER;