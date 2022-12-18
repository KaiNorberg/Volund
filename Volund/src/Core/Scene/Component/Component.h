#pragma once

#include "Time/Time.h"

#include "Core/EventDispatcher/Event.h"

namespace Volund
{
	class Scene;

	using Entity = uint64_t;

	class Component
	{
	public:

		Entity GetEntity() const;

		virtual void OnCreate() {};

		virtual void OnDelete() {};

		virtual void OnUpdate(TimeStep) {};

		virtual void OnEvent(Event*) {};

		Component() = default;

		virtual ~Component() = default;
	
	private:
		friend class Scene;

		void Init(Entity entity);

		Entity _Entity = NULL;
	};
}
