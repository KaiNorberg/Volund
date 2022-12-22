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

	private:

		bool _ShouldTerminate = false;

		int _ActiveThreads = 0;

		std::queue<ThreadJob> _JobQueue;

		std::vector<std::thread> _Threads;

		std::condition_variable _Condition;
		std::mutex _Mutex;

		void Loop();
	};
}