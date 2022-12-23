#include "PCH/PCH.h"

#include "Application.h"

#include "Time/Time.h"

#include "Renderer/Renderer.h"
#include "Renderer/RenderingAPI/RenderingAPI.h"

#include "ThreadPool/ThreadPool.h"

namespace Volund
{
	void Application::Run()
	{
		this->OnRun();
		this->Loop();
	}

	void Application::Terminate()
	{
		this->OnTerminate();
		this->_ShouldRun = false;
	}

	bool Application::ShouldRun() const
	{
		return this->_ShouldRun;
	}

	Ref<EventDispatcher> Application::GetEventDispatcher()
	{
		return this->_EventDispatcher;
	}

	void Application::EventCallback(Event* E)
	{
		VOLUND_PROFILE_FUNCTION();

		this->OnEvent(E);

		for (const auto& View : this->_Modules)
		{
			for (const auto& Module : View)
			{
				Module->OnEvent(E);
			}
		}	
		
		switch (E->GetType())
		{
		case VL::EventType::WINDOW_CLOSE:
		{
			this->Terminate();
		}
		break;
		}
	}

	void Application::OnEvent(Event* E)
	{}
	void Application::OnUpdate(TimeStep TS)
	{}
	void Application::OnRender()
	{}
	void Application::OnRun()
	{}
	void Application::OnTerminate()
	{}

	void Application::Loop()
	{
		std::chrono::time_point<std::chrono::steady_clock> OldTime = std::chrono::high_resolution_clock::now();

		while (this->_ShouldRun)
		{
			VOLUND_PROFILING_START(uint64_t(this));

			std::chrono::duration<double> Duration = std::chrono::high_resolution_clock::now() - OldTime;
			OldTime = std::chrono::high_resolution_clock::now();
			TimeStep TS = TimeStep(Duration.count());

			this->_ThreadPool.Submit([this, TS]()
			{
				this->OnUpdate(TS);

				for (const auto& View : this->_Modules)
				{
					for (const auto& Module : View)
					{
						Module->OnUpdate(TS);
					}
				}
			});	

			Renderer::Begin();

			this->OnRender();

			for (const auto& View : this->_Modules)
			{
				for (const auto& Module : View)
				{
					Module->OnRender();
				}
			}	

			while (this->_ThreadPool.Busy());

			Renderer::End();

			VOLUND_PROFILING_END();
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

		this->_EventDispatcher = std::make_shared<EventDispatcher>(this);
	}

	Application::~Application()
	{

	}
}
