#include "Application.h"

#include "Event.h"
#include "Time.h"

namespace Volund
{
	void Application::Run()
	{
		if (this->m_dispatcher == nullptr)
		{
			VOLUND_ERROR("App not connected!");
			return;
		}

		this->Loop();
	}

	bool Application::ShouldRun() const
	{
		return this->m_shouldRun;
	}

	std::shared_ptr<Window> Application::GetWindow()
	{
		return this->m_window;
	}

	std::shared_ptr<Dispatcher> Application::GetDispatcher()
	{
		return this->m_dispatcher;
	}

	void Application::Terminate()
	{
		this->m_shouldRun = false;
	}

	void Application::EventCallback(const Event& e)
	{
		this->Procedure(e);

		for (const auto& [typeId, view] : this->m_modules)
		{
			for (const auto& module : view)
			{
				module->Procedure(e);
			}
		}
	}

	void Application::Loop()
	{
		VOLUND_PROFILE_FUNCTION();

		auto startTime = std::chrono::high_resolution_clock::now();

		while (this->m_shouldRun)
		{
			VOLUND_PROFILE_SCOPE("MainLoop");

			TimeStep ts = TimeStep(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count());
			startTime = std::chrono::high_resolution_clock::now();

			this->m_window->Flush();
			this->m_window->Update();

			Event updateEvent = Event(VOLUND_EVENT_UPDATE);
			VOLUND_EVENT_UPDATE_SET_TIMESTEP(updateEvent, float(ts));

			this->m_dispatcher->Enqueue(updateEvent);
			this->m_dispatcher->Enqueue(Event(VOLUND_EVENT_RENDER));

			this->m_dispatcher->Dispatch();
		}
	}

	Application::Application()
	{
#ifdef _DEBUG
		VOLUND_INFO("Initializing application (Debug)...");
#elif defined(NDEBUG)
		VOLUND_INFO("Initializing application (Release)...");
#else
		VOLUND_WARNING("Initializing application (Unknown)...");
#endif

		this->m_dispatcher = std::make_shared<Dispatcher>([this](const Event& e)
		{
			this->EventCallback(e);
		});

		this->m_window = std::make_shared<Window>(this->m_dispatcher, 1980, 1080, false);
		this->m_window->SetTitle("Volund");
	}

	Application::~Application()
	{
		for (auto& [TypeID, View] : this->m_modules)
		{
			for (auto& module : View)
			{
				module->OnDetach();

				module.reset();
			}
		}

		VOLUND_INFO("Application terminated");
	}
}
