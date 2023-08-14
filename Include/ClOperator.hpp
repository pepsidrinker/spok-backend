#pragma once

#include "ClState.hpp"

#include <memory>

class ClOperator
{
  public:
    typedef int (*EXECUTE_FUNCTION_POINTER)(STATE_POINTER& p_source_state, STATE_POINTER& po_destination_pointer);
    EXECUTE_FUNCTION_POINTER m_execute_function;

    ClOperator();
    ~ClOperator();
    int Execute(STATE_POINTER& p_source_state, STATE_POINTER& po_destination_state);
    static std::shared_ptr<ClOperator> Create(EXECUTE_FUNCTION_POINTER p_execute_function);
    
};

typedef std::shared_ptr<ClOperator> OPERATOR_POINTER;

