
#include "Component/Component.h"

namespace Volund
{
	Entity Component::GetEntity() const
	{
		return this->m_entity;
	}

	std::shared_ptr<Scene> Component::GetScene() const
	{
		return this->m_scene.lock();
	}

	void Component::Init(Entity entity, std::weak_ptr<Scene> scene)
	{
		this->m_entity = entity;
		this->m_scene = scene;
	}
}