#include "ClOperator.hpp"

ClOperator::ClOperator()
{
}

ClOperator::~ClOperator()
{
}

std::shared_ptr<ClOperator> ClOperator::Create(EXECUTE_FUNCTION_POINTER p_execute_function)
{
    if(p_execute_function == nullptr)
    {
        return nullptr;
    }

    std::shared_ptr<ClOperator> new_operator = std::make_shared<ClOperator>();
    new_operator->m_execute_function = p_execute_function;
    std::size_t execute_function_address = (std::size_t)(p_execute_function);
    new_operator->m_uid = std::to_string(execute_function_address);
    return new_operator;
}


int ClOperator::Execute(void* p_problem_instance)
{
    if(this->m_execute_function == nullptr)
    {
        return 0;
    }

    return this->m_execute_function(p_problem_instance);
}

bool ClOperator::IsEqualTo(const ClOperator& p_operator)
{
    return this->m_execute_function == p_operator.m_execute_function;
}