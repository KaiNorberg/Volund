#pragma once

#include "Time/Time.h"

namespace Volund
{
	class SimpleComponent
	{
	public:

		virtual void OnInit() {};

		virtual void OnRemove() {};

		virtual void OnUpdate(TimeStep TS) {};

		virtual const std::string Type() { return "SimpleComponent"; }

	private:

	};
}

