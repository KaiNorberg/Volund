#include "PCH/PCH.h"

#include "Application.h"

#include "Scene/Scene.h"

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
		VOLUND_CORE_INFO("Initializing application...");

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