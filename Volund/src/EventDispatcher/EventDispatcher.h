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

		EventDispatcher(std::function<void(const Event&)> eventCallback);

	private:

		std::function<void(const Event&)> m_EventCallback;
	};
}
