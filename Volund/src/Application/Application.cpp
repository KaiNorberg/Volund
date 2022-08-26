#include "PCH/PCH.h"

#include "Application.h"

#include "Scene/Scene.h"
#include "Input/Input.h"
#include "Time/Time.h"
#include "Renderer/Renderer.h"

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

	void Application::Loop()
	{
		std::chrono::time_point<std::chrono::steady_clock> OldTime = std::chrono::high_resolution_clock::now();

		while (!this->_Window.ShouldClose())
		{
			std::chrono::duration<double> Duration = std::chrono::high_resolution_clock::now() - OldTime;
			OldTime = std::chrono::high_resolution_clock::now();
			TimeStep TS = TimeStep(Duration.count());

			this->_Window.Clear();

			for (Layer* L : _LayerStack)
			{
				L->OnUpdate(TS);
			}

			this->_Context->Flush();

			this->_Window.PollEvents();

			this->_EventDispatcher.Dispatch();		
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
		Renderer::LoadJSONSettings();

		this->_Context = Context::Create(&this->_Window);
	}

	Application::~Application()
	{
		for (auto const& L : this->_LayerStack)
		{
			L->OnDetach();
			delete L;
		}
		this->_LayerStack.clear();

		if (this->_Context != nullptr)
		{
			delete this->_Context;
			this->_Context = nullptr;
		}
	}
}