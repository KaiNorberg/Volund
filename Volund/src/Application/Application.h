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

		Context* _Context = nullptr;

		EventDispatcher _EventDispatcher = EventDispatcher(this);

		Window _Window = Window(&_EventDispatcher);

		std::vector<Layer*> _LayerStack;

		void Loop();
	};
}

