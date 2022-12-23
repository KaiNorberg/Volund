#pragma once

#include "Time/Time.h"
#include "EventDispatcher/Event.h"

namespace Volund
{
	class Application;

	class Module
	{
	public:

		virtual void OnAttach(Application* App) = 0;

		virtual void OnDetach() = 0;

		virtual void Procedure(const Event& E) = 0;

		Module();

		virtual ~Module();

	private:
	};
}