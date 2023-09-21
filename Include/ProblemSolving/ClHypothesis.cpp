#include "ClHypothesis.hpp"

ClHypothesis::ClHypothesis()
{
    this->m_operator = nullptr;
    this->m_predictive_state = nullptr;
    this->m_current_state = nullptr;
}

ClHypothesis::~ClHypothesis(){}


std::string ClHypothesis::GetUID()
{
    if(this->m_current_state == nullptr || this->m_operator == nullptr)
    {
        return "INVALID_UID";
    }

    XXH64_hash_t current_state_hash = XXH64(this->m_current_state->m_state_variables.data(), this->m_current_state->m_state_variables.size() * sizeof(float), 0);

    std::string result = std::to_string(current_state_hash);    
    result.append(this->m_operator->m_uid);

    return result;
}


// int ClHypothesis::Create(std::size_t p_number_of_variables, std::shared_ptr<ClOperator> p_operator, std::shared_ptr<ClHypothesis>& po_new_instance)
// {
//     if(p_number_of_variables == 0)
//     {
//         return -1;
//     }

//     if(p_operator == nullptr)
//     {
//         return -2;
//     }

//     po_new_instance = std::make_shared<ClHypothesis>();
//     po_new_instance->m_operator = p_operator;
    
//     int result = 0;
//     result = ClState::Create(p_number_of_variables, po_new_instance->m_predictive_state);
//     if(result != 0)
//     {
//         return -3;
//     }

//     return 1;
// }