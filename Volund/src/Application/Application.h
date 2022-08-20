#pragma once

#include "Window/Window.h"

namespace Volund
{
	class Scene;

	class Application
	{
	public:

		Window EngineWindow;

		VOLUND_API void LoadScene(std::string const& FilePath);

		VOLUND_API void Run();

		VOLUND_API Application();
			
		VOLUND_API virtual ~Application() = default;

	private:

		void Loop();

		Scene* CurrentScene = nullptr;
	};
}

