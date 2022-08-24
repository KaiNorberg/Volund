#include "PCH/PCH.h"

#include "Application.h"

#include "Scene/Scene.h"

#include "Input/Input.h"

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
		while (!this->_Window.ShouldClose())
		{
			this->_Window.Clear();

			for (Layer* L : _LayerStack)
			{
				L->OnUpdate();
			}

			this->_Window.SwapBuffers();
			this->_Window.PollEvents();

			this->_EventDispatcher.Dispatch();
		}
	}

	Application::Application()
	{

#ifdef VOLUND_DEBUG
		VOLUND_CORE_INFO("Initializing application (Debug)...");
#elif VOLUND_RELEASE
		VOLUND_CORE_INFO("Initializing application (Release)...");
#elif VOLUND_DIST
		VOLUND_CORE_INFO("Initializing application (Distribution)...");
#else 		
		VOLUND_CORE_WARNING("Initializing application (Unknown)...");
#endif

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
		{
			VOLUND_CORE_ERROR("Failed to initialize OpenGL context");
		}
	}

	Application::~Application()
	{
		for (auto const& L : this->_LayerStack)
		{
			L->OnDetach();
			delete L;
		}
	}
}