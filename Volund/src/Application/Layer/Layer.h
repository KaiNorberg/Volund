#pragma once

#include "Time/Time.h"

#include "EventDispatcher/Event.h"

namespace Volund
{
	class Application;

	class Layer
	{
	public:

		Application* GetApp();

		virtual void OnAttach() {};

		virtual void OnDetach() {};

		virtual void OnUpdate(TimeStep TS) {};
	
		virtual void OnEvent(Event* E) {};

		virtual ~Layer() {}
	private:		
		friend class Application;

		void SetParent(Application* Parent);

		Application* _Parent = nullptr;
	};
}