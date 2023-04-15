#include "PCH/PCH.h"

#include "Application.h"

#include "Time/Time.h"

#include "Renderer/Renderer.h"
#include "Renderer/RenderingAPI/RenderingAPI.h"

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

		auto startTime = std::chrono::high_resolution_clock::now();

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

			DeferredTaskHandler::Execute();
		}
	}

	void Application::Connect(Ref<EventDispatcher> dispatcher)
	{
		this->m_EventDispatcher = dispatcher;
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
