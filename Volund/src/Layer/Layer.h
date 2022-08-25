#pragma once

#include "Time/Time.h"

namespace Volund
{
	class Layer
	{
	public:
		virtual void OnAttach() {};

		virtual void OnDetach() {};

		virtual void OnUpdate(TimeStep TS) {};
	
		virtual ~Layer() {}
	};
}