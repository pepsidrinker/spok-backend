#pragma once

#include <memory>
#include <vector>
#include <iostream>

class ClState
{
    public:
    std::vector<float> m_state_variables;

    ClState();
    ~ClState();
    static int Create(std::size_t p_number_of_variable, std::shared_ptr<ClState>& po_new_state);
    bool IsEqualTo(const ClState& p_state);    
    std::shared_ptr<ClState> Clone();
    void Print();    
};

typedef std::shared_ptr<ClState> STATE_POINTER;