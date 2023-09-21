#include "ClOperator.hpp"

ClOperator::ClOperator()
{
}

ClOperator::~ClOperator()
{
}

int ClOperator::Create(EXECUTE_FUNCTION_POINTER p_execute_function,  std::shared_ptr<ClOperator>& po_new_instance)
{
    if(p_execute_function == nullptr)
    {
        return -1;
    }

    std::shared_ptr<ClOperator> new_operator = std::make_shared<ClOperator>();
    new_operator->m_execute_function = p_execute_function;
    std::size_t execute_function_address = (std::size_t)(p_execute_function);
    new_operator->m_uid = std::to_string(execute_function_address);

    po_new_instance = new_operator;

    return 1;
}


int ClOperator::Execute(void* p_problem_instance, STATE_POINTER p_result_state)
{
    if(this->m_execute_function == nullptr)
    {
        return 0;
    }

    return this->m_execute_function(p_problem_instance, p_result_state);
}

bool ClOperator::IsEqualTo(const ClOperator& p_operator)
{
    return this->m_execute_function == p_operator.m_execute_function;
}