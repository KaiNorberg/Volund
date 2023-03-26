#pragma once

#include "Event.h"

#include "Scene/Scene.h"

namespace Volund
{
	class Application;

	class EventDispatcher
	{
	public:

		void Dispatch(const Event& e);

		EventDispatcher(Application* app);

	private:

		Application* m_App = nullptr;
	};
}
