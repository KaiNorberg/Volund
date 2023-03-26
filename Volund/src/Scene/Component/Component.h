#pragma once

#include "Time/Time.h"

#include "EventDispatcher/Event.h"

namespace Volund
{
	class Scene;

	using Entity = uint64_t;

	class Component
	{
	public:

		virtual void OnCreate() {}
		
		virtual void OnDestroy() {}

		virtual void Procedure(const Event& e) {}

		Entity GetEntity() const;

		Scene* GetScene() const;

		Component() = default;

		virtual ~Component() = default;
	
	private:
		friend class Scene;

		void Init(Entity entity, Scene* scene);

		Entity m_Entity = NULL;

		Scene* m_Scene = nullptr;
	};
}
