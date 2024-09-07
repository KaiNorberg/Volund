#pragma once

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

        bool m_ShouldTerminate = false;

        uint8_t m_ActiveWorkerCount = 0;

        std::queue<Task> m_TaskQueue;
        std::vector<std::thread> m_Workers;

        std::condition_variable m_Condition;
        std::mutex m_Mutex;
    };

    template<typename Func, typename ...Args>
    inline void ThreadPool::Submit(Func&& func, Args && ...args)
    {
        {
            std::unique_lock<std::mutex> lock(this->m_Mutex);
            this->m_TaskQueue.emplace([=] { func(std::forward<Args>(args)...); });
        }
        this->m_Condition.notify_one();
    }
}