#include "PCH/PCH.h"

#include "Entity.h"

namespace Volund
{
	bool Entity::Error()
	{
		return ErrorOccured;
	}

	bool Entity::AddComponent(JSON ComponentJSON)
	{
		if (!ComponentJSON.contains("Name"))
		{
			Console::LogWarning("Component without specified type found");
			return false;
		}
		std::string Name = ComponentJSON["Name"];
		if (this->HasComponent(Name))
		{
			Console::LogWarning("Cant give an entity a component that it already has.");
			return false;
		}
	
		if (Name == TRANSFORM_COMPONENT)
		{
			this->Components[Name] = new Transform(this, ComponentJSON);
		}
		else		
			if (Name == RENDERER_COMPONENT)
		{
			this->Components[Name] = new Renderer(this, ComponentJSON);
		}
		else
		{
			return false;
		}

		return true;
	}

	bool Entity::RemoveComponent(std::string const& Name)
	{
		if (!HasComponent(Name))
		{
			Console::LogWarning("Cant remove a component from a object without that component.");
			return false;
		}

		delete this->Components[Name];
		this->Components.erase(Name);

		return true;
	}

	SimpleComponent* Entity::GetComponent(std::string const& Name)
	{
		if (!HasComponent(Name))
		{
			Console::LogWarning("Cant get a component from a object without that component.");
			return nullptr;
		}

		return this->Components.at(Name);
	}

	bool Entity::HasComponent(std::string const& Name) const
	{
		return this->Components.find(Name) != this->Components.end();
	}

	Entity::Entity(JSON EntityJSON)
	{
		if (EntityJSON.contains("Name") && EntityJSON["Name"].is_string())
		{
			this->Name = EntityJSON["Name"].get<std::string>();
		}
		if (EntityJSON.contains("Components") && EntityJSON["Components"].is_array())
		{
			for (JSON Entry : EntityJSON["Components"])
			{
				this->AddComponent(Entry);
			}
		}		
	}
}