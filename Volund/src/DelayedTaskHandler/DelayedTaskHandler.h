#pragma once

namespace Volund
{
	class DelayedTaskHandler
	{
	public:

		static void DelayTask(std::function<void()> task);

		static void Execute();

	private:

		static inline std::mutex m_Mutex;

		static inline std::vector<std::function<void()>> m_Tasks;
	};
}