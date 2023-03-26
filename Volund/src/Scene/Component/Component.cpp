#include "PCH/PCH.h"

#include "Component.h"

namespace Volund
{
	Entity Component::GetEntity() const
	{
		return this->m_Entity;
	}

	Scene* Component::GetScene() const
	{
		return this->m_Scene;
	}

	void Component::Init(Entity entity, Scene* scene)
	{
		this->m_Entity = entity;
		this->m_Scene = scene;
	}
}
