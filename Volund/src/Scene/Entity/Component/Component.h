#pragma once

#include "Time/Time.h"

#include "EventDispatcher/Event.h"

#include "VML/VML.h"

namespace Volund
{
	class Entity;

	class Component
	{
	public:
		Entity* GetEntity() const;

		virtual void OnCreate() {};

		virtual void OnDelete() {};

		virtual void OnUpdate(TimeStep TS) {};

		virtual void OnEvent(Event* E) {};

		virtual VML Serialize() = 0;

		Component() = default;

	private:
		friend class Entity;

		void SetParent(Entity* Parent);

		Entity* _Parent = nullptr;
	};
}
