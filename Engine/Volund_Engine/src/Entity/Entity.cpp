#include "PCH/PCH.h"

#include "Entity.h"

#include "Component/NativeComponents/NativeComponents.h"

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
	
		if (Name == "Transform3D")
		{
			this->Components[Name] = new Transform3D(this, ComponentJSON);
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
		for (JSON Entry : EntityJSON)
		{
			this->AddComponent(Entry);
		}
	}
}