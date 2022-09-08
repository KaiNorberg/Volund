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

		 Application();
			
		 virtual ~Application();

	protected:

		bool _ShouldRun = true;

	private:

		void Loop();

		std::vector<Ref<Layer>> _LayerStack;
	};
}

