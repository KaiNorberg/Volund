#pragma once

namespace Volund
{
	using ThreadJob = std::function<void()>;

	class ThreadPool
	{
	public:

		static void Init();

		static void QueueJob(ThreadJob Job);
		
		static void Terminate();

		static bool Busy();

	private:

		static inline bool _ShouldTerminate = false;
		static inline bool _IsInitialized = false;

		static inline std::mutex _Mutex;
		static inline std::condition_variable _MutexCondition;

		static inline std::vector<std::thread> _Threads;
		static inline std::queue<ThreadJob> _Jobs;

		static void Loop();
	};
}