#include "PCH/PCH.h"

#include "Component.h"

namespace Volund
{
	Entity Component::GetEntity() const
	{
		return this->m_Entity;
	}

	Ref<Scene> Component::GetScene() const
	{
		return this->m_Scene.lock();
	}

	void Component::Init(Entity entity, WeakRef<Scene> scene)
	{
		this->m_Entity = entity;
		this->m_Scene = scene;
	}
}
