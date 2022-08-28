#pragma once

#include "Time/Time.h"

namespace Volund
{
	class Component
	{
	public:

		virtual void OnInit() = 0;

		virtual void OnRemove() = 0;

		virtual void OnUpdate(TimeStep TS) = 0;

	private:

	};
}

