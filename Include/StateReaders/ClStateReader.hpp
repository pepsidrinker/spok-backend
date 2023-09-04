#pragma once

#include <memory>
#include "../ClState.hpp"

class ClStateReader
{
    protected:
        bool m_flag_is_initialized;
    public:
        ClStateReader();
        virtual ~ClStateReader();
        virtual int Initialize() = 0;
        virtual int WaitForNewState(std::shared_ptr<ClState>& po_new_state) = 0;
        virtual int Uninitialize() = 0;
};