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
			VOLUND_CORE_WARNING("Duplicate entity detected");
			return nullptr;
		}

		this->_Entities.push_back(NewEntity);

		return NewEntity;
	}

	bool Scene::RemoveEntity(std::string const& Name)
	{
		for (int i = 0; i < this->_Entities.size(); i++)
		{
			if (this->_Entities[i]->GetName() == Name)
			{
				this->_Entities.erase(this->_Entities.begin() + i);		
				return true;
			}
		}

		VOLUND_CORE_WARNING("Entity not found (%s)", Name);
		return false;
	}

	Entity* Scene::GetEntity(std::string const& Name)
	{
		for (int i = 0; i < this->_Entities.size(); i++)
		{
			if (this->_Entities[i]->GetName() == Name)
			{
				return this->_Entities[i];
			}
		}

		VOLUND_CORE_WARNING("Entity not found (%s)", Name);
		return nullptr;
	}

	bool Scene::HasEntity(std::string const& Name) const
	{
		for (int i = 0; i < this->_Entities.size(); i++)
		{
			if (this->_Entities[i]->GetName() == Name)
			{
				return true;
			}
		}

		return false;
	}

	void Scene::OnUpdate()
	{
		for (auto const& EntityPointer : this->_Entities)
		{
			EntityPointer->OnUpdate();
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
		for (auto const& EntityPointer : this->_Entities)
		{
			delete EntityPointer;
		}
	}
}