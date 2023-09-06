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
    return new_operator;
}


int ClOperator::Execute(STATE_POINTER& p_source_state, STATE_POINTER& po_destination_state)
{
    if(this->m_execute_function == nullptr)
    {
        return 0;
    }

    return this->m_execute_function(p_source_state, po_destination_state);
}

bool ClOperator::IsEqualTo(const ClOperator& p_operator)
{
    return this->m_execute_function == p_operator.m_execute_function);
}