#pragma once

#include <memory>
#include <vector>
#include <iostream>

class ClState
{
    public:
    std::vector<int> m_state_variables;

    ClState();
    ~ClState();
    static int Create(std::size_t p_number_of_variable, std::shared_ptr<ClState>& po_new_state);
    void Print();
};

typedef std::shared_ptr<ClState> STATE_POINTER;