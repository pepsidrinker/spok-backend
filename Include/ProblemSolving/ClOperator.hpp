#pragma once

#include "../ClState.hpp"

#include <memory>
#include <string>

class ClOperator
{
    typedef int (*EXECUTE_FUNCTION_POINTER)(void* p_problem_instance);
  
    protected:
        EXECUTE_FUNCTION_POINTER m_execute_function;

    public:
        std::string m_uid;

        ClOperator();
        ~ClOperator();
        int Execute(void* p_problem_instance);
        static std::shared_ptr<ClOperator> Create(EXECUTE_FUNCTION_POINTER p_execute_function);
        bool IsEqualTo(const ClOperator& p_operator);    
    
    
};

typedef std::shared_ptr<ClOperator> OPERATOR_POINTER;

