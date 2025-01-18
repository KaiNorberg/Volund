#include "Job.h"

namespace Volund
{
	Job::Job(Task task, Task cleanupTask)
	{
		this->m_Task = task;
		this->m_CleanupTask = cleanupTask;
	}
}
