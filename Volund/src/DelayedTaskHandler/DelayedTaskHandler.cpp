#include "PCH/PCH.h"
#include "DelayedTaskHandler.h"

namespace Volund
{
	void DelayedTaskHandler::DelayTask(std::function<void()> task)
	{
#ifdef VOLUND_ENABLE_PROFILING
		Task();
#else
		std::unique_lock lock(m_Mutex);

		m_Tasks.push_back(task);
#endif
	}

	void DelayedTaskHandler::Execute()
	{
		std::unique_lock lock(m_Mutex);

		for (auto& task : m_Tasks)
		{
			task();
		}
		m_Tasks.clear();
	}
}