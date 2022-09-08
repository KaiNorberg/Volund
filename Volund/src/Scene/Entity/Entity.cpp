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

	JSON Entity::Serialize() const
	{
		JSON EntityJSON;

		EntityJSON.AddEntry("Name", this->_Name);

		JSON ComponentsJSON;

		for (const auto& ComponentView : this->_Components)
		{
			for (const auto& Component : ComponentView)
			{
				ComponentsJSON.PushBack(Component->Serialize());
			}
		}

		EntityJSON.AddEntry("Components", ComponentsJSON);

		return EntityJSON;
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
