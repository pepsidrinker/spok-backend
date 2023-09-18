#include "ClProblemStore.hpp"

ClProblemStore::ClProblemStore(){}
ClProblemStore::~ClProblemStore(){}

int ClProblemStore::Create(PROBLEM_STORE_POINTER& po_new_instance)
{
    po_new_instance = std::make_shared<ClProblemStore>();
    return 1;
}