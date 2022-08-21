#pragma once

#include "Window/Window.h"
#include "EventDispatcher/EventDispatcher.h"

namespace Volund
{
	class Scene;

	class VOLUND_API Application
	{
	public:

		void LoadScene(std::string const& FilePath);

		void Run();

		Application();
			
		virtual ~Application() = default;

	protected:

		EventDispatcher _EventDispatcher;

		Window _Window = Window(&_EventDispatcher);

		Scene* _LoadedScene = nullptr;

	private:

		void Loop();
	};
}

