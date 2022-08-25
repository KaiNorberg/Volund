#include "PCH/PCH.h"

#include "Entity.h"

namespace Volund
{
	std::unordered_map<std::string, uint64_t> Entity::_ComponentTypeIDs =
	{
		{TRANSFORM_COMPONENT, typeid(Transform).hash_code()},
		{RENDERER_COMPONENT, typeid(Renderer).hash_code()},
	};

	Scene* Entity::GetParent()
	{
		return this->_Parent;
	}

	std::string Entity::GetName()
	{
		return this->_Name;
	}

	bool Entity::Error()
	{
		return _ErrorOccured;
	}

	SimpleComponent* Entity::AddComponent(JSON ComponentJSON)
	{
		if (!ComponentJSON.Contains("Type"))
		{
			VOLUND_CORE_WARNING("Component without specified type found");
			return nullptr;
		}
		std::string Type = ComponentJSON["Type"];
		if (this->HasComponent(Type))
		{
			VOLUND_CORE_WARNING("Cant give an entity a component that it already has.");
			return nullptr;
		}
	
		if (Type == TRANSFORM_COMPONENT)
		{
			this->_Components[_ComponentTypeIDs[Type]] = new Transform(this, ComponentJSON);
		}
		else if (Type == RENDERER_COMPONENT)
		{
			this->_Components[_ComponentTypeIDs[Type]] = new Renderer(this, ComponentJSON);
		}
		else
		{
			return nullptr;
		}

		return this->_Components[_ComponentTypeIDs[Type]];
	}

	bool Entity::RemoveComponent(std::string const& Type)
	{
		if (!HasComponent(Type))
		{
			VOLUND_CORE_WARNING("Cant remove a component from a object without that component.");
			return false;
		}

		delete this->_Components[_ComponentTypeIDs[Type]];
		this->_Components.erase(_ComponentTypeIDs[Type]);

		return true;
	}

	SimpleComponent* Entity::GetComponent(std::string const& Type)
	{
		if (!HasComponent(Type))
		{
			VOLUND_CORE_WARNING("Cant get a component from a object without that component.");
			return nullptr;
		}

		return this->_Components[_ComponentTypeIDs[Type]];
	}

	bool Entity::HasComponent(std::string const& Type) const
	{
		return this->_Components.find(_ComponentTypeIDs[Type]) != this->_Components.end();
	}

	void Entity::OnUpdate(TimeStep TS)
	{
		for (auto const& [TypeID, Component] : this->_Components)
		{
			Component->OnUpdate(TS);
		}
	}

	Entity::Entity(Scene* Parent, JSON EntityJSON)
	{
		this->_Parent = Parent;

		if (EntityJSON.Contains("Type"))
		{
			this->_Name = EntityJSON["Type"].GetAs<std::string>();
		}
		if (EntityJSON.Contains("Components"))
		{
			for (int i = 0; i < EntityJSON["Components"].Size(); i++)
			{
				this->AddComponent(EntityJSON["Components"][i]);
			}
		}
	}

	Entity::~Entity()
	{
		for (auto const& [TypeID, Component] : this->_Components)
		{
			delete Component;
		}
	}
}