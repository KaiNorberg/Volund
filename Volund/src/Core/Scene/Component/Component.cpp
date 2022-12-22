#include "PCH/PCH.h"

#include "Component.h"

namespace Volund
{
	Entity Component::GetEntity() const
	{
		return this->_Entity;
	}

	Scene* Component::GetScene() const
	{
		return this->_Scene;
	}

	void Component::Init(Entity entity, Scene* scene)
	{
		this->_Entity = entity;
		this->_Scene = scene;
	}
}
