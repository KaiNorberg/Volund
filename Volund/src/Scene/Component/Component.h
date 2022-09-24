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

		virtual void OnCreate() {};

		virtual void OnDelete() {};

		virtual void OnUpdate(TimeStep) {};

		virtual void OnEvent(Event*) {};

		virtual VML Serialize() = 0;

		Component() = default;

		virtual ~Component() = default;
	
	protected:

		Entity GetEntity() const;

		Scene* GetScene() const;

	private:
		friend class Scene;

		void Init(Scene* scene, Entity entity);

		Scene* _Scene = nullptr;
		Entity _Entity = NULL;
	};
}
