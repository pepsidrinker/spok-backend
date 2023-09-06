#pragma once

#include "ClState.hpp"

#include <memory>
#include <string>

class ClOperator
{
  public:
    typedef int (*EXECUTE_FUNCTION_POINTER)(STATE_POINTER& p_source_state, STATE_POINTER& po_destination_pointer);
    EXECUTE_FUNCTION_POINTER m_execute_function;
    std::string m_uid;

    ClOperator();
    ~ClOperator();
    int Execute(STATE_POINTER& p_source_state, STATE_POINTER& po_destination_state);
    static std::shared_ptr<ClOperator> Create(EXECUTE_FUNCTION_POINTER p_execute_function);
    bool IsEqualTo(const ClOperator& p_operator);    
    
    
};

typedef std::shared_ptr<ClOperator> OPERATOR_POINTER;

