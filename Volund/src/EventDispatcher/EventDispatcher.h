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

		void Connect(Ref<Application> app);

		EventDispatcher();

	private:

		WeakRef<Application> m_App;
	};
}
