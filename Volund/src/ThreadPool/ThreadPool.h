#pragma once

namespace Volund
{
	using Task = std::function<void()>;

	class ThreadPool
	{
	public:

		void Submit(Task task);
		
		bool Busy();

		ThreadPool();

		~ThreadPool();

		static ThreadPool& GetGlobalPool();

	private:

		static ThreadPool m_GlobalPool;

		bool m_ShouldTerminate = false;

		int m_ActiveThreads = 0;

		std::queue<Task> m_TaskQueue;

		std::vector<std::thread> m_Threads;

		std::condition_variable m_Condition;
		std::mutex m_Mutex;

		void Loop();
	};
}


/// The global threadpool is only supposed to be used for temporary jobs, for example loading a file.
/// Any job submited to the globalpool must not wait for any external signal, it must allays finish on its own without external changes.
#define VOLUND_THREADPOOL_SUBMIT(...) ::Volund::ThreadPool::GetGlobalPool().Submit(__VA_ARGS__)
#define VOLUND_THREADPOOL_BUSY() ::Volund::ThreadPool::GetGlobalPool().Busy()