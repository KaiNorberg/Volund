#pragma once

#include "Event.hpp"
#include "Job.hpp"

#include "Scene.hpp"

#include <functional>

namespace Volund
{
    class VOLUND_API Dispatcher
    {
    public:
        void Enqueue(const Event& e);
        void Enqueue(const Job& job);
        void Enqueue(const Task& deferredTask);
        void Dispatch();
        Dispatcher(std::function<void(const Event&)> eventCallback);
        ~Dispatcher();
    private:
        std::mutex m_mutex;
        std::function<void(const Event&)> m_eventCallback;
        std::shared_ptr<ThreadPool> m_threadPool;
        std::queue<Job> m_jobQueue;
        std::queue<Task> m_cleanupQueue;
        std::queue<Event> m_eventQueue;
        std::queue<Task> m_deferredQueue;
    };
}
