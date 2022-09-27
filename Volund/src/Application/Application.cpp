#include "PCH/PCH.h"

#include "Application.h"

#include "Time/Time.h"

namespace Volund
{
	void Application::Run()
	{
		this->OnRun();
		this->Loop();
	}

	Ref<EventDispatcher> Application::GetEventDispatcher()
	{
		return this->_EventDispatcher;
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

	void Application::OnEvent(Event* E)
	{

	}

	void Application::OnUpdate(TimeStep TS)
	{

	}

	void Application::OnRun()
	{

	}

	void Application::OnTerminate()
	{

	}

	void Application::Loop()
	{
		std::chrono::time_point<std::chrono::steady_clock> OldTime = std::chrono::high_resolution_clock::now();

		while (this->_ShouldRun)
		{
			std::chrono::duration<double> Duration = std::chrono::high_resolution_clock::now() - OldTime;
			OldTime = std::chrono::high_resolution_clock::now();
			TimeStep TS = TimeStep(Duration.count());

			this->OnUpdate(TS);
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
		
		this->_EventDispatcher = Ref<EventDispatcher>(new EventDispatcher(this));
	}

	Application::~Application()
	{

	}
}
