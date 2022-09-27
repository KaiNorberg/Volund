#pragma once

#include "Time/Time.h"

#include "Container/Container.h"

#include "EventDispatcher/EventDispatcher.h"

namespace Volund
{
	class Application
	{
	public:

		void Run();

		Ref<EventDispatcher> GetEventDispatcher();

		void Terminate();

		bool ShouldRun() const;

		virtual void OnEvent(Event* E);
		
		virtual void OnUpdate(TimeStep TS);

		virtual void OnRun();

		virtual void OnTerminate();

		Application();

		virtual ~Application();

	private:
		
		void Loop();

		bool _ShouldRun = true;

		Ref<EventDispatcher> _EventDispatcher;
	};
}
