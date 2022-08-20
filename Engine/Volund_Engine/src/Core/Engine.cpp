#include "PCH/PCH.h"

#include "Engine.h"

namespace Volund
{
	void Engine::LoadScene(std::string const& FilePath)
	{
		Console::Log("Loading scene (", FilePath, ")...");

		if (this->CurrentScene != nullptr)
		{
			delete this->CurrentScene;
		}

		this->CurrentScene = new Scene((std::filesystem::path)FilePath);

		this->Loop();
	}	
	
	void Engine::Loop()
	{
		while (!this->EngineWindow.ShouldClose())
		{
			this->EngineWindow.Clear();

			if (this->CurrentScene != nullptr)
			{
				this->CurrentScene->Update();
			}

			this->EngineWindow.SwapBuffers();
			this->EngineWindow.PollEvents();
		}
	}

	Engine::Engine()
	{
		Console::Log("Initializing Engine...");

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