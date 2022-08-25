#pragma once

#include "Window/Window.h"
#include "EventDispatcher/EventDispatcher.h"
#include "Layer/Layer.h"
#include "Scene/Scene.h"

#include "Context/Context.h"

namespace Volund
{
	class Application
	{
	public:

		 void Run();

		 void AttachLayer(Layer* L);

		 Application();
			
		 virtual ~Application();

	protected:

		Context* _Context;

		EventDispatcher _EventDispatcher;

		Window _Window = Window(&_EventDispatcher);

	private:

		std::vector<Layer*> _LayerStack;

		void Loop();
	};
}

