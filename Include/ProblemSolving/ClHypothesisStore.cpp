#include "ClHypothesisStore.hpp"

ClHypothesisStore::ClHypothesisStore(){}
ClHypothesisStore::~ClHypothesisStore(){}

int ClHypothesisStore::Create(std::shared_ptr<ClHypothesisStore>& po_new_instance)
{
    po_new_instance = std::make_shared<ClHypothesisStore>();
    return 1;
}