
#include "Component.h"

namespace Volund
{
	Entity Component::GetEntity() const
	{
		return this->m_Entity;
	}

	std::shared_ptr<Scene> Component::GetScene() const
	{
		return this->m_Scene.lock();
	}

	void Component::Init(Entity entity, std::weak_ptr<Scene> scene)
	{
		this->m_Entity = entity;
		this->m_Scene = scene;
	}
}
