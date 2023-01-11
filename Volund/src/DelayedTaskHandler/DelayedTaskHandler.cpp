#include "PCH/PCH.h"
#include "DelayedTaskHandler.h"

namespace Volund
{
	void DelayedTaskHandler::DelayTask(std::function<void()> Task)
	{
#ifdef VOLUND_ENABLE_PROFILING
		Task();
#else
		std::unique_lock Lock(_Mutex);

		_Tasks.push_back(Task);
#endif
	}

	void DelayedTaskHandler::Execute()
	{
		std::unique_lock Lock(_Mutex);

		for (auto& Task : _Tasks)
		{
			Task();
		}
		_Tasks.clear();
	}
}