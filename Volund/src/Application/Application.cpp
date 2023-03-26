#include "PCH/PCH.h"

#include "Application.h"

#include "Time/Time.h"

#include "Renderer/Renderer.h"
#include "Renderer/RenderingAPI/RenderingAPI.h"

#include "ThreadPool/ThreadPool.h"

#include "DelayedTaskHandler/DelayedTaskHandler.h"

namespace Volund
{
	void Application::Run()
	{
		this->OnRun();
		this->Loop();
	}

	bool Application::ShouldRun() const
	{
		return this->m_ShouldRun;
	}

	Ref<EventDispatcher> Application::GetEventDispatcher()
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

		std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::high_resolution_clock::now();

		while (this->m_ShouldRun)
		{
			VOLUND_PROFILE_SCOPE("MainLoop");

			TimeStep ts = TimeStep(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count());
			startTime = std::chrono::high_resolution_clock::now();

			this->m_ThreadPool.Submit([this, ts]()
			{
				Event updateEvent = Event(EventType::Update);
				VOLUND_EVENT_UPDATE_SET_TIMESTEP(updateEvent, float(ts));
				this->m_EventDispatcher->Dispatch(updateEvent);
			});

			Renderer::Begin();
			this->m_EventDispatcher->Dispatch(Event(EventType::Render));
			Renderer::End();

			while (this->m_ThreadPool.Busy());

			DelayedTaskHandler::Execute();
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

		this->m_EventDispatcher = std::make_shared<EventDispatcher>(this);
	}

	Application::~Application()
	{
		for (const auto& [TypeID, View] : this->m_Modules)
		{
			for (const auto& module : View)
			{
				module->OnDetach();
			}
		}
	}
}
