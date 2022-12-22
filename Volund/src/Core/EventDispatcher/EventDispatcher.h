#pragma once

#include "Event.h"

#include "Core/Scene/Scene.h"

namespace Volund
{
	class Application;

	class EventDispatcher
	{
	public:

		void Dispatch(Event* E);

		EventDispatcher(Application* App);

	private:

		Application* _App = nullptr;
	};

}
