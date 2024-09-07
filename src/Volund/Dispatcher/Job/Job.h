#pragma once

#include "ThreadPool/ThreadPool.h"

namespace Volund
{
    class Dispatcher;

    class Job
    {
    public:

        Job(Task task, Task cleanupTask);

    private:

        friend class Dispatcher;

        Task m_Task;
        Task m_CleanupTask;
    };
}