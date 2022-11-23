#pragma once

#include "Time/Time.h"
#include "EventDispatcher/Event.h"

namespace Volund
{
	class Application;

	class Module
	{
	public:

		virtual void OnEvent(Event* E);

		virtual void OnUpdate(TimeStep TS);

		virtual void OnAttach(Application* App);

		virtual void OnDestroy();

		Module();

		virtual ~Module();

	private:
	};
}