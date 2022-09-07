#pragma once

#include "Time/Time.h"

#include "EventDispatcher/Event.h"

namespace Volund
{
	class Entity;

	class Component
	{
	public:

		Entity* GetEntity();

		virtual void OnCreate() {};

		virtual void OnDelete() {};

		virtual void OnUpdate(TimeStep TS) {};

		virtual	void OnEvent(Event* E) {};

		virtual JSON Serialize() = 0;

		Component() = default;

	private:
		friend class Entity;

		void SetParent(Entity* Parent);

		Entity* _Parent = nullptr;
	};
}

