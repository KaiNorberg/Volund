#include "PCH/PCH.h"

#include "Application.h"

#include "Scene/Scene.h"

#include "Input/Input.h"

#include "Context/OpenGLContext.h"
#include "Shader/OpenGLShader.h"

namespace Volund
{
	uint32_t VertexArray;

	uint32_t VertexBuffer;

	uint32_t IndexBuffer;

	OpenGLShader TestShader;

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

			glClearColor(0.5, 0, 0, 1);

			glViewport(0, 0, this->_Window.GetSize().x, this->_Window.GetSize().y);

			TestShader.Use();

			glBindVertexArray(VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* L : _LayerStack)
			{
				L->OnUpdate();
			}

			this->_Context->SwapBuffers();

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

		this->_Context = new OpenGLContext(&this->_Window);

		VOLUND_CORE_INFO("OpenGL Renderer: %s", (const char*)glGetString(GL_RENDERER));
		VOLUND_CORE_INFO("OpenGL Version: %s", (const char*)glGetString(GL_VERSION));
		VOLUND_CORE_INFO("OpenGL Vendor: %s", (const char*)glGetString(GL_VENDOR));
		VOLUND_CORE_INFO("GLFW Version: %s", glfwGetVersionString());

		TestShader.Init("Shaders/Test.shader");

		glGenVertexArrays(1, &VertexArray);
		glBindVertexArray(VertexArray);

		glGenBuffers(1, &VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

		float Verticies[9] =
		{
			-0.5f, -0.5, 0.0,
			0.5, -0.5, 0.0,
			0.0, 0.5, 0.0
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(Verticies), Verticies, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);

		uint32_t Indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
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