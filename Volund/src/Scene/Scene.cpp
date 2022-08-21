#include "PCH/PCH.h"

#include "Scene.h"

namespace Volund
{
	bool Scene::Error()
	{
		return _ErrorOccured;
	}

	Entity* Scene::AddEntity(JSON EntityJSON)
	{
		Entity* NewEntity = new Entity(this, EntityJSON);

		if (NewEntity->Error())
		{
			return nullptr;
		}
		if (this->HasEntity(NewEntity->GetName()))
		{
			Console::LogWarning("Duplicate entity detected");
			return nullptr;
		}

		this->_Entities[NewEntity->GetName()] = NewEntity;

		return this->_Entities[NewEntity->GetName()];
	}

	bool Scene::RemoveEntity(std::string const& Name)
	{
		if (!this->HasEntity(Name))
		{
			Console::LogWarning("Entity not found (", Name, ")");
			return false;
		}

		this->_Entities.erase(Name);

		return true;
	}

	Entity* Scene::GetEntity(std::string const& Name)
	{
		if (!this->HasEntity(Name))
		{
			Console::LogWarning("Entity not found (", Name, ")");
			return nullptr;
		}

		return this->_Entities[Name];
	}

	bool Scene::HasEntity(std::string const& Name) const
	{
		return this->_Entities.find(Name) != this->_Entities.end();
	}

	void Scene::Update()
	{
		for (auto const& [Name, EntityPointer] : this->_Entities)
		{
			EntityPointer->Update();
		}
	}

	Scene::Scene(std::filesystem::path FilePath)
	{
		this->_Name = FilePath.filename().string();

		JSON ConfigFile = LoadJSON(CONFIG_JSON);
		JSON EntitiesJSON = LoadJSON(FilePath.string() + "\\" + ConfigFile["Scene"]["EntitiesJSON"].get<std::string>());

		for (JSON Entry : EntitiesJSON)
		{
			this->AddEntity(Entry);
		}
	}

	Scene::~Scene()
	{
		for (auto const& [Name, EntityPointer] : this->_Entities)
		{
			delete EntityPointer;
		}
	}
}