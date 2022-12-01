#pragma once

#include "Time/Time.h"

#include "EventDispatcher/Event.h"

#include "VML/VML.h"

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

		virtual VML Serialize() = 0;

		Component() = default;

		virtual ~Component() = default;
	
	private:
		friend class Scene;

		void Init(Entity entity);

		Entity _Entity = NULL;
	};
}
