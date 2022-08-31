#include "PCH/PCH.h"

#include "Application.h"

#include "Scene/Scene.h"
#include "Input/Input.h"
#include "Time/Time.h"

namespace Volund
{
	void Application::Run()
	{
		this->Loop();		
	}

	void Application::AttachLayer(Layer* L)
	{
		this->_LayerStack.push_back(L);
		L->OnAttach();
	}

	void Application::Restart()
	{
		::Volund::ShouldRun = true;
		this->_ShouldRun = false;
	}

	void Application::Terminate()
	{
		::Volund::ShouldRun = false;
		this->_ShouldRun = false;
	}

	bool Application::ShouldRun()
	{
		return this->_ShouldRun;
	}

	void Application::Loop()
	{
		std::chrono::time_point<std::chrono::steady_clock> OldTime = std::chrono::high_resolution_clock::now();

		while (this->_ShouldRun)
		{
			std::chrono::duration<double> Duration = std::chrono::high_resolution_clock::now() - OldTime;
			OldTime = std::chrono::high_resolution_clock::now();
			TimeStep TS = TimeStep(Duration.count());

			this->_Window->Clear();

			for (Layer* L : _LayerStack)
			{
				L->OnUpdate(TS);
			}

			this->_Window->PollEvents();
		}
	}

	void Application::EventCallback(Event* E)
	{
		switch (E->GetType())
		{
		case EventType::WINDOW_CLOSE:
		{
			this->Terminate();
		}
		break;
		}

		for (Layer* L : _LayerStack)
		{
			L->OnEvent(E);
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
		this->_EventDispatcher.reset(new EventDispatcher(this));
		
		this->_Window.reset(new Window(this->_EventDispatcher));		
		
		this->_Renderer.reset(new Renderer(this->_Window));
	}

	Application::~Application()
	{
		for (auto const& L : this->_LayerStack)
		{
			L->OnDetach();
			delete L;
		}
		this->_LayerStack.clear();
	}
}