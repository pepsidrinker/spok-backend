#pragma once

#include <memory>
#include <vector>

class ClProblem;


class ClProblemStore
{
    public:
    typedef std::shared_ptr<ClProblemStore> PROBLEM_STORE_POINTER;   

    public:
       
        std::vector< std::shared_ptr<ClProblem> > m_problems;
        
    public:
        ClProblemStore();
        ~ClProblemStore();

        static int Create(PROBLEM_STORE_POINTER& po_new_instance);        
};

typedef std::shared_ptr<ClProblemStore> PROBLEM_STORE_POINTER;   
