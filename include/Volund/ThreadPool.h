#pragma once

#include <functional>
#include <cstdint>
#include <queue>
#include <thread>
#include <condition_variable>

namespace Volund
{
    using Task = std::function<void()>;

    class ThreadPool
    {
    public:
        template<typename Func, typename... Args>
        void Submit(Func&& func, Args&&... args);
        bool Busy();
        uint8_t GetActiveWorkerCount();
        ThreadPool(uint8_t threadCount);
        ~ThreadPool();
    private:
        void Loop();
        bool m_shouldTerminate = false;
        uint8_t m_activeWorkerCount = 0;
        std::queue<Task> m_taskQueue;
        std::vector<std::thread> m_workers;
        std::condition_variable m_condition;
        std::mutex m_mutex;
    };

    template<typename Func, typename ...Args>
    inline void ThreadPool::Submit(Func&& func, Args && ...args)
    {
        {
            std::unique_lock<std::mutex> lock(this->m_mutex);
            this->m_taskQueue.emplace([=] { func(std::forward<Args>(args)...); });
        }
        this->m_condition.notify_one();
    }
}
