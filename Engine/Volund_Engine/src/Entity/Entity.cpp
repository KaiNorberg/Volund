#include "PCH/PCH.h"

#include "Entity.h"

namespace Volund
{
	std::unordered_map<std::string, uint64_t> Entity::ComponentTypeIDs =
	{
		{TRANSFORM_COMPONENT, typeid(Transform).hash_code()},
		{RENDERER_COMPONENT, typeid(Renderer).hash_code()},
	};

	Scene* Entity::GetParent()
	{
		return this->Parent;
	}

	std::string Entity::GetName()
	{
		return this->Name;
	}

	bool Entity::Error()
	{
		return ErrorOccured;
	}

	SimpleComponent* Entity::AddComponent(JSON ComponentJSON)
	{
		if (!ComponentJSON.contains("Type"))
		{
			Console::LogWarning("Component without specified type found");
			return nullptr;
		}
		std::string Type = ComponentJSON["Type"];
		if (this->HasComponent(Type))
		{
			Console::LogWarning("Cant give an entity a component that it already has.");
			return nullptr;
		}
	
		if (Type == TRANSFORM_COMPONENT)
		{
			this->Components[ComponentTypeIDs[Type]] = new Transform(this, ComponentJSON);
		}
		else if (Type == RENDERER_COMPONENT)
		{
			this->Components[ComponentTypeIDs[Type]] = new Renderer(this, ComponentJSON);
		}
		else
		{
			return nullptr;
		}

		return this->Components[ComponentTypeIDs[Type]];
	}

	bool Entity::RemoveComponent(std::string const& Type)
	{
		if (!HasComponent(Type))
		{
			Console::LogWarning("Cant remove a component from a object without that component.");
			return false;
		}

		delete this->Components[ComponentTypeIDs[Type]];
		this->Components.erase(ComponentTypeIDs[Type]);

		return true;
	}

	SimpleComponent* Entity::GetComponent(std::string const& Type)
	{
		if (!HasComponent(Type))
		{
			Console::LogWarning("Cant get a component from a object without that component.");
			return nullptr;
		}

		return this->Components[ComponentTypeIDs[Type]];
	}

	bool Entity::HasComponent(std::string const& Type) const
	{
		return this->Components.find(ComponentTypeIDs[Type]) != this->Components.end();
	}

	void Entity::Update()
	{
		for (auto const& [TypeID, Component] : this->Components)
		{
			Component->Update();
		}
	}

	Entity::Entity(Scene* Parent, JSON EntityJSON)
	{
		this->Parent = Parent;

		if (EntityJSON.contains("Type") && EntityJSON["Type"].is_string())
		{
			this->Name = EntityJSON["Type"].get<std::string>();
		}
		if (EntityJSON.contains("Components") && EntityJSON["Components"].is_array())
		{
			for (JSON Entry : EntityJSON["Components"])
			{
				this->AddComponent(Entry);
			}
		}		
	}

	Entity::~Entity()
	{
		for (auto const& [TypeID, Component] : this->Components)
		{
			delete Component;
		}
	}
}