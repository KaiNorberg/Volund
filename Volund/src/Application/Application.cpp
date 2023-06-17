#include "PCH/PCH.h"

#include "Application.h"

#include "Time/Time.h"

#include "ThreadPool/ThreadPool.h"

#include "DeferredTaskHandler/DeferredTaskHandler.h"

#include <glad/glad.h>

namespace Volund
{
	void Application::Run()
	{
		if (this->m_EventDispatcher == nullptr)
		{
			VOLUND_ERROR("App not connected!");
			return;
		}

		this->OnRun();
		this->Loop();
	}

	bool Application::ShouldRun() const
	{
		return this->m_ShouldRun;
	}

	Ref<EventDispatcher> Application::GetDispatcher()
	{
		return this->m_EventDispatcher;
	}

	void Application::Terminate()
	{
		this->OnTerminate();
		this->m_ShouldRun = false;
	}

	void Application::Loop()
	{
		VOLUND_PROFILE_FUNCTION();

		auto startTime = std::chrono::high_resolution_clock::now();

		while (this->m_ShouldRun)
		{
			VOLUND_PROFILE_SCOPE("MainLoop");

			TimeStep ts = TimeStep(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count());
			startTime = std::chrono::high_resolution_clock::now();

			this->m_ThreadPool.Submit([this, ts]()
			{
				Event updateEvent = Event(VOLUND_EVENT_TYPE_UPDATE);
				VOLUND_EVENT_UPDATE_SET_TIMESTEP(updateEvent, float(ts));
				this->m_EventDispatcher->Dispatch(updateEvent);
			});

			this->m_EventDispatcher->Dispatch(Event(VOLUND_EVENT_TYPE_RENDER));

			while (this->m_ThreadPool.Busy());

			DeferredTaskHandler::Execute();
		}
	}

	void Application::Dispatch(const Event& e)
	{
		this->Procedure(e);

		for (const auto& [typeId, view] : this->m_Modules)
		{
			for (const auto& module : view)
			{
				module->Procedure(e);
			}
		}
	}

	Application::Application()
	{
#ifdef VOLUND_DEBUG
		VOLUND_INFO("Initializing application (Debug)...");
#elif VOLUND_RELEASE
		VOLUND_INFO("Initializing application (Release)...");
#elif VOLUND_DIST
		VOLUND_INFO("Initializing application (Distribution)...");
#else
		VOLUND_WARNING("Initializing application (Unknown)...");
#endif	

		this->m_EventDispatcher = std::make_shared<EventDispatcher>([this](const Event& e)
		{
			this->Dispatch(e);
		});
	}

	Application::~Application()
	{
		for (auto& [TypeID, View] : this->m_Modules)
		{
			for (auto& module : View)
			{
				module->OnDetach();
			}
		}
	}
}
