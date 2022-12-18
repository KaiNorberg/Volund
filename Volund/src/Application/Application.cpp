#include "PCH/PCH.h"

#include "Application.h"

#include "Time/Time.h"

#include "Renderer/Renderer.h"
#include "Renderer/RenderingAPI/RenderingAPI.h"

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

	void Application::EventCallback(Event* E)
	{
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

			for (const auto& View : this->_Modules)
			{
				for (const auto& Module : View)
				{
					Module->OnUpdate(TS);
				}
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
	}

	Application::~Application()
	{

	}
}
