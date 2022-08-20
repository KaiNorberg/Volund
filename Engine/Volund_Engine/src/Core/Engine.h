#pragma once

#include "Scene/Scene.h"

#include "Window/Window.h"

namespace Volund
{
	class Engine
	{
	public:

		Window EngineWindow;

		void LoadScene(std::string const& FilePath);

		Engine();
			
	private:

		void Loop();

		Scene* CurrentScene;
	};
}

