#pragma once

#include <memory>
#include <vector>

#include "ClHypothesis.hpp"

class ClHypothesisStore
{
    public:
        std::vector<ClHypothesis> m_hypotheses;
        ClHypothesisStore();
        ~ClHypothesisStore();
        static int Create(std::shared_ptr<ClHypothesisStore>& po_new_instance);
};

typedef std::shared_ptr<ClHypothesisStore> HYPOTHESIS_STORE_POINTER;