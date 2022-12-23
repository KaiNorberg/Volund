#pragma once

#include "Event.h"

#include "Scene/Scene.h"

namespace Volund
{
	class Application;

	class EventDispatcher
	{
	public:

		void Dispatch(const Event& E);

		EventDispatcher(Application* App);

	private:

		Application* _App = nullptr;
	};

}
