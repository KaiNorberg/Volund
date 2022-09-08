#include "PCH/PCH.h"

#include "Entity.h"

namespace Volund
{
	std::string Entity::GetName()
	{
		return this->_Name;
	}

	Scene* Entity::GetScene()
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

	JSON Entity::Serialize()
	{
		JSON EntityJSON;

		EntityJSON.AddEntry("Name", this->_Name);

		JSON ComponentsJSON;

		for (auto const& ComponentView : this->_Components)
		{
			for (auto const& Component : ComponentView)
			{
				ComponentsJSON.PushBack(Component->Serialize());
			}
		}

		EntityJSON.AddEntry("Components", ComponentsJSON);
		
		return EntityJSON;
	}

	Entity::Entity(Scene* Parent, std::string const& Name)
	{
		this->_Parent = Parent;
		this->_Name = Name;
	}

	Entity::~Entity()
	{
		for (auto const& ComponentView : this->_Components)
		{
			for (auto const& Component : ComponentView)
			{
				Component->OnDelete();
			}
		}
	}
}