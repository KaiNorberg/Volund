#pragma once

#include "ThreadPool.h"

namespace Volund
{
    class Dispatcher;

    class Job
    {
    public:
        Job(Task task, Task cleanupTask);
    private:
        friend class Dispatcher;

        Task m_task;
        Task m_cleanupTask;
    };
}
