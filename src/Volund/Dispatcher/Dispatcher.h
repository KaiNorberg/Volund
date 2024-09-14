#pragma once

#include "Event.h"
#include "Job.h"

#include "Scene/Scene.h"

namespace Volund
{
    class Dispatcher
    {
    public:

        void Enqueue(const Event& e);

        void Enqueue(const Job& job);

        void Enqueue(const Task& deferredTask);

        void Dispatch();

        Dispatcher(std::function<void(const Event&)> eventCallback);

        ~Dispatcher();

    private:

        std::mutex m_Mutex;

        std::function<void(const Event&)> m_EventCallback;

        std::shared_ptr<ThreadPool> m_ThreadPool;

        std::queue<Job> m_JobQueue;
        std::queue<Task> m_CleanupQueue;
        std::queue<Event> m_EventQueue;
        std::queue<Task> m_DeferredQueue;
    };
}
