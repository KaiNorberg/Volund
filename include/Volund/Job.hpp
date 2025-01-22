#pragma once

#include "ThreadPool.hpp"

namespace Volund
{
    class Dispatcher;
    
    class VOLUND_API Job
    {
    public:
        Job(Task task, Task cleanupTask);
    private:
        friend class Dispatcher;
        Task m_task;
        Task m_cleanupTask;
    };
}
