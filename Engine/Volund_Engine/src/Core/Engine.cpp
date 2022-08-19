#include "PCH/PCH.h"

#include "Engine.h"

namespace Volund
{
	void Engine::LoadScene(std::string const& FilePath)
	{
		Console::Log("Loading scene (", FilePath, ")...");

		this->CurrentScene = Scene((std::filesystem::path)FilePath);

		this->Loop();
	}	
	
	void Engine::Loop()
	{
		while (!this->EngineWindow.ShouldClose())
		{
			this->EngineWindow.Clear();


			this->EngineWindow.SwapBuffers();
			this->EngineWindow.PollEvents();
		}
	}

	Engine::Engine()
	{
		Console::Log("Initializing Engine...");

		/*if (!glfwInit())
		{
			Console::LogError("GLFW init failed.");
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

		JSON ConfigFile = JSON::Load(CONFIG_JSON);
		this->LoadScene(ConfigFile["Engine"]["MainScene"].get<std::string>());
	}
}