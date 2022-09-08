#include "PCH/PCH.h"

#include "Component.h"

namespace Volund
{
	Entity* Component::GetEntity() const
	{
		return this->_Parent;
	}

	void Component::SetParent(Entity* Parent)
	{
		this->_Parent = Parent;
	}
}
