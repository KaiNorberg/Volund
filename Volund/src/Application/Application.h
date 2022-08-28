#pragma once

#include "Window/Window.h"
#include "EventDispatcher/EventDispatcher.h"
#include "Layer/Layer.h"
#include "Scene/Scene.h"

#include "Renderer/Context/Context.h"

namespace Volund
{
	class Application
	{
	public:

		 void Run();

		 void AttachLayer(Layer* L);

		 void Terminate();

		 bool ShouldRun();

		 Application();
			
		 virtual ~Application();

	protected:

		bool _ShouldRun = true;

	private:

		Ref<EventDispatcher> _EventDispatcher;
		Ref<Window> _Window;

		std::vector<Layer*> _LayerStack;

		void Loop();
	};
}

