#include "PCH/PCH.h"

#include "Entity.h"

namespace Volund
{
	std::string Entity::GetName()
	{
		return this->_Name;
	}

	Scene* Entity::GetScene() const
	{
		return this->_Parent;
	}

	void Entity::OnEvent(Event* E) const
	{
		for (const auto& ComponentView : this->_Components)
		{
			for (const auto& Component : ComponentView)
			{
				Component->OnEvent(E);
			}
		}
	}

	void Entity::OnUpdate(TimeStep TS) const
	{
		for (const auto& ComponentView : this->_Components)
		{
			for (const auto& Component : ComponentView)
			{
				Component->OnUpdate(TS);
			}
		}
	}

	VML Entity::Serialize() const
	{
		VML EntityVML;

		uint32_t i = 0;
		for (const auto& ComponentView : this->_Components)
		{
			for (const auto& Component : ComponentView)
			{
				EntityVML.PushBack("Component" + std::to_string(i), Component->Serialize());
				i++;
			}
		}

		return EntityVML;
	}

	Entity::Entity(Scene* Parent, const std::string& Name)
	{
		this->_Parent = Parent;
		this->_Name = Name;
	}

	Entity::~Entity()
	{
		for (const auto& ComponentView : this->_Components)
		{
			for (const auto& Component : ComponentView)
			{
				Component->OnDelete();
			}
		}
	}
}
