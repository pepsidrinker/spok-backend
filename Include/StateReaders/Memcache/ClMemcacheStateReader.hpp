#include "../ClStateReader.hpp"

#include <libmemcached/memcached.h>

#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <iostream>

class ClMemcacheStateReader : public ClStateReader
{
    protected:
        memcached_st* m_memcache_handle;
        memcached_server_st* m_memcache_server_list;
        std::size_t m_last_processed_timestep;

    public:
        ClMemcacheStateReader();
        virtual ~ClMemcacheStateReader();
        int Initialize() override;
        int WaitForNewState(std::shared_ptr<ClState>& po_new_state) override;
        int Uninitialize() override;
        static int Create(std::shared_ptr<ClMemcacheStateReader>& po_new_instance);
};

typedef std::shared_ptr<ClMemcacheStateReader> MEMCACHE_STATE_READER_POINTER;