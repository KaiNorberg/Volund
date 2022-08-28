#include "PCH/PCH.h"

#include "Component.h"

namespace Volund
{
	Entity* Component::GetParent()
	{
		return this->_Parent;
	}

	void Component::SetParent(Entity* Parent)
	{
		this->_Parent = Parent;
	}
}

