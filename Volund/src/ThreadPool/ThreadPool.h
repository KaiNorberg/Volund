#pragma once

namespace Volund
{
	using ThreadJob = std::function<void()>;

	class ThreadPool
	{
	public:

		void Submit(ThreadJob job);
		
		bool Busy();

		ThreadPool();

		~ThreadPool();

		static ThreadPool& GetGlobalPool();

	private:

		static ThreadPool m_GlobalPool;

		bool m_ShouldTerminate = false;

		int m_ActiveThreads = 0;

		std::queue<ThreadJob> m_JobQueue;

		std::vector<std::thread> m_Threads;

		std::condition_variable m_Condition;
		std::mutex m_Mutex;

		void Loop();
	};
}

#define VOLUND_THREADPOOL_SUBMIT(...) ::Volund::ThreadPool::GetGlobalPool().Submit(__VA_ARGS__)
#define VOLUND_THREADPOOL_BUSY() ::Volund::ThreadPool::GetGlobalPool().Busy()