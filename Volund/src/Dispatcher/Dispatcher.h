#pragma once

#include "Event/Event.h"
#include "Job/Job.h"

#include "Scene/Scene.h"

namespace Volund
{
	class Dispatcher
	{
	public:

		void Dispatch(const Event& e);

		void Dispatch(const Job& job);

		void Execute();

		Dispatcher(std::function<void(const Event&)> eventCallback);

	private:

		std::mutex m_Mutex;

		std::function<void(const Event&)> m_EventCallback;

		Ref<ThreadPool> m_ThreadPool;

		std::queue<Task> m_CleanupQueue;
		std::queue<Event> m_EventQueue;
	};
}
