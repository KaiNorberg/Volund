#include "Job.hpp"

namespace Volund
{
	Job::Job(Task task, Task cleanupTask)
	{
		this->m_task = task;
		this->m_cleanupTask = cleanupTask;
	}
}
