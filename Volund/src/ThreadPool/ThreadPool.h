#pragma once

namespace Volund
{
	using ThreadJob = std::function<void()>;

	class ThreadPool
	{
	public:

		void Submit(ThreadJob Job);
		
		bool Busy();

		ThreadPool();

		~ThreadPool();

		static ThreadPool& GetGlobalPool();

	private:

		static ThreadPool _GlobalPool;

		bool _ShouldTerminate = false;

		int _ActiveThreads = 0;

		std::queue<ThreadJob> _JobQueue;

		std::vector<std::thread> _Threads;

		std::condition_variable _Condition;
		std::mutex _Mutex;

		void Loop();
	};
}

#define VOLUND_THREADPOOL_SUBMIT(...) ::Volund::ThreadPool::GetGlobalPool().Submit(__VA_ARGS__)
#define VOLUND_THREADPOOL_BUSY() ::Volund::ThreadPool::GetGlobalPool().Busy()