#pragma once

#include "../ClState.hpp"

#include <memory>
#include <string>

class ClOperator
{
    typedef int (*EXECUTE_FUNCTION_POINTER)(void* p_problem_instance, STATE_POINTER& p_result_state);
  
    protected:
        EXECUTE_FUNCTION_POINTER m_execute_function;

    public:
        std::string m_uid;

        ClOperator();
        ~ClOperator();
        int Execute(void* p_problem_instance, STATE_POINTER& p_result_state);
        static int Create(EXECUTE_FUNCTION_POINTER p_execute_function, std::shared_ptr<ClOperator>& po_new_instance);
        bool IsEqualTo(const ClOperator& p_operator);    
    
    
};

typedef std::shared_ptr<ClOperator> OPERATOR_POINTER;

