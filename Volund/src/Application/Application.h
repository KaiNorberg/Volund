#pragma once

#include "Window/Window.h"
#include "EventDispatcher/EventDispatcher.h"
#include "Layer/Layer.h"
#include "Scene/Scene.h"

#include "Renderer/Context/Context.h"
#include "Renderer/Renderer.h"

namespace Volund
{
	class Application
	{
	public:

		 void Run();

		 void AttachLayer(Layer* L);

		 void Terminate();

		 bool ShouldRun();

		 void EventCallback(Event* E);

		 Application();
			
		 virtual ~Application();

	protected:

		bool _ShouldRun = true;

	private:

		void Loop();

		Ref<EventDispatcher> _EventDispatcher;
		Ref<Window> _Window;

		std::vector<Ref<Layer>> _LayerStack;
	};
}

