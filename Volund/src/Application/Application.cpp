#include "PCH/PCH.h"

#include "Application.h"

#include "Time/Time.h"

namespace Volund
{
	void Application::Run()
	{
		this->Loop();
	}

	void Application::Terminate()
	{
		this->_ShouldRun = false;
	}

	bool Application::ShouldRun() const
	{
		return this->_ShouldRun;
	}

	void Application::Loop() const
	{
		std::chrono::time_point<std::chrono::steady_clock> OldTime = std::chrono::high_resolution_clock::now();

		while (this->_ShouldRun)
		{
			std::chrono::duration<double> Duration = std::chrono::high_resolution_clock::now() - OldTime;
			OldTime = std::chrono::high_resolution_clock::now();
			TimeStep TS = TimeStep(Duration.count());

			for (const auto& View : this->_LayerContainer)
			{
				for (const auto& Layer : View)
				{
					Layer->OnUpdate(TS);
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
		for (const auto& View : this->_LayerContainer)
		{
			for (const auto& Layer : View)
			{
				Layer->OnDetach();
			}
		}
	}
}
