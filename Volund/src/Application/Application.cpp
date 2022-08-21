#include "PCH/PCH.h"

#include "Application.h"

#include "Scene/Scene.h"

namespace Volund
{
	void Application::LoadScene(std::string const& FilePath)
	{
		Console::Log("Loading scene (", FilePath, ")...");

		if (this->_LoadedScene != nullptr)
		{
			delete this->_LoadedScene;
		}

		this->_LoadedScene = new Scene((std::filesystem::path)FilePath);

		this->Loop();
	}	

	void Application::Run()
	{
		JSON ConfigFile = LoadJSON(CONFIG_JSON);

		if (ConfigFile.contains("Engine") && ConfigFile["Engine"].contains("MainScene"))
		{
			this->LoadScene(ConfigFile["Engine"]["MainScene"].get<std::string>());
		}
		else
		{
			Console::LogError("Config file does not define a MainScene");
		}
	}
	
	void Application::Loop()
	{
		while (!this->_Window.ShouldClose())
		{
			this->_Window.Clear();

			if (this->_LoadedScene != nullptr)
			{
				this->_LoadedScene->Update();
			}

			this->_Window.SwapBuffers();
			this->_Window.PollEvents();

			this->_EventDispatcher.Dispatch();
		}
	}

	Application::Application()
	{
		Console::Log("Initializing Volund...");

		/*if (!glewinit())
		{
			Console::LogError("GLEW init failed.");
		}

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glDepthFunc(GL_LEQUAL);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(ErrorCallback, NULL);*/
	}
}