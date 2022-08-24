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

		VOLUND_API void Run();

		VOLUND_API void AttachLayer(Layer* L);

		VOLUND_API Application();
			
		VOLUND_API virtual ~Application();

	protected:

		Context* _Context;

		EventDispatcher _EventDispatcher;

		Window _Window = Window(&_EventDispatcher);

	private:

		std::vector<Layer*> _LayerStack;

		void Loop();
	};
}

