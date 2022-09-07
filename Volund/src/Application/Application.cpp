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
		this->_LayerStack.push_back(Ref<Layer>(L));
		L->OnAttach();
	}

	void Application::Terminate()
	{
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

			for (Ref<Layer> L : _LayerStack)
			{
				L->OnUpdate(TS);
			}

			this->_Window->Update();
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

		for (Ref<Layer> L : _LayerStack)
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
	
		JSON ConfigJSON = JSON::Load(VOLUND_CONFIG_JSON);

		this->_EventDispatcher.reset(new EventDispatcher(this));

		// Window

		uint32_t WindowWidth = ConfigJSON["Window"]["Width"].GetAs<uint32_t>();
		uint32_t WindowHeight = ConfigJSON["Window"]["Height"].GetAs<uint32_t>();
		bool WindowFullScreen = ConfigJSON["Window"]["FullScreen"].GetAs<bool>();

		this->_Window.reset(new Window(this->_EventDispatcher, WindowWidth, WindowHeight, WindowFullScreen));

		this->_Window->SetTitle(ConfigJSON["Window"]["Title"]);
		this->_Window->SetCursorMode(ConfigJSON["Window"]["CursorMode"]);

		// Renderer Settings

		if (RenderingAPI::GetSelectedAPI() == RenderingAPI::API::NONE)
		{
			RenderingAPI::SelectAPI(ConfigJSON["Renderer"]["API"].GetAs<std::string>());
		}

		Renderer::SetWindow(this->_Window);

		Renderer::GetContext()->SetVSync(ConfigJSON["Renderer"]["VSync"].GetAs<bool>());
	}

	Application::~Application()
	{
		for (auto const& L : this->_LayerStack)
		{
			L->OnDetach();
		}
		this->_LayerStack.clear();

		if (Renderer::GetWindow() == this->_Window)
		{
			Renderer::SetWindow(nullptr);
		}
	}
}