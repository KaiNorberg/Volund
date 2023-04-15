#include "PCH/PCH.h"
#include "DeferredTaskHandler.h"

namespace Volund
{
	void DeferredTaskHandler::DeferTask(std::function<void()> task)
	{
#ifdef VOLUND_DISABLE_MULTITHREADING
		task();
#else
		std::unique_lock lock(m_Mutex);

		m_Tasks.push_back(task);
#endif
	}

	void DeferredTaskHandler::Execute()
	{
		std::unique_lock lock(m_Mutex);

		for (auto& task : m_Tasks)
		{
			task();
		}
		m_Tasks.clear();
	}
}