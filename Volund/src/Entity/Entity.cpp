#include "PCH/PCH.h"

#include "Entity.h"

namespace Volund
{
	std::string Entity::GetName()
	{
		return this->_Name;
	}

	Scene* Entity::GetParent()
	{
		return this->_Parent;
	}

	void Entity::OnEvent(Event* E)
	{
		for (auto const& ComponentView : this->_Components)
		{
			for (auto const& Component : ComponentView)
			{
				Component->OnEvent(E);
			}
		}
	}

	void Entity::OnUpdate(TimeStep TS)
	{
		for (auto const& ComponentView : this->_Components)
		{
			for (auto const& Component : ComponentView)
			{
				Component->OnUpdate(TS);
			}
		}
	}

	Entity::Entity(Scene* Parent, std::string const& Name)
	{
		this->_Parent = Parent;
		this->_Name = Name;
	}

	Entity::~Entity()
	{

	}
}