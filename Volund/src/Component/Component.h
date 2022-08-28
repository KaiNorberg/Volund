#pragma once

#include "Time/Time.h"

namespace Volund
{
	class Entity;

	class Component
	{
	public:

		Entity* GetParent();

		virtual void OnCreate() {};

		virtual void OnUpdate(TimeStep TS) {};

		virtual void OnDelete() {};

		Component() = default;

	private:
		friend class Entity;

		void SetParent(Entity* Parent);

		Entity* _Parent;
	};
}

