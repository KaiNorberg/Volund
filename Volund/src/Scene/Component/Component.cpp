#include "PCH/PCH.h"

#include "Component.h"

namespace Volund
{
	Entity Component::GetEntity() const
	{
		return this->_Entity;
	}

	void Component::Init(Entity entity)
	{
		this->_Entity = entity;
	}
}
