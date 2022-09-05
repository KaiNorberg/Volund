#include "PCH/PCH.h"

#include "Scene.h"

#include "EventDispatcher/Event.h"
#include "Component/Transform/Transform.h"

namespace Volund
{
	Ref<Entity> Scene::CreateEntity(std::string const& Name)
	{
		Ref<Entity> NewEntity = Ref<Entity>(new Entity(this, Name));

		if (this->HasEntity(NewEntity->GetName()))
		{
			VOLUND_WARNING("Duplicate entity detected");
			return nullptr;
		}

		this->_Entities.push_back(NewEntity);

		return NewEntity;
	}

	Ref<Entity> Scene::CreateEntity(std::string const& Name, Vec3 const& Position, Vec3 const& Rotation, Vec3 const& Scale)
	{
		Ref<Entity> NewEntity = this->CreateEntity(Name);

		NewEntity->CreateComponent<Transform>(Position, Rotation, Scale);

		return NewEntity;
	}

	bool Scene::DeleteEntity(std::string const& Name)
	{
		for (int i = 0; i < this->_Entities.size(); i++)
		{
			if (this->_Entities[i]->GetName() == Name)
			{
				this->_Entities.erase(this->_Entities.begin() + i);		
				return true;
			}
		}

		VOLUND_ERROR("Entity not found (%s)", Name.c_str());
		return false;
	}

	Ref<Entity> Scene::GetEntity(std::string const& Name)
	{
		for (int i = 0; i < this->_Entities.size(); i++)
		{
			if (this->_Entities[i]->GetName() == Name)
			{
				return this->_Entities[i];
			}
		}

		VOLUND_ERROR("Entity not found (%s)", Name.c_str());
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

	void Scene::Update(TimeStep TS)
	{
		this->OnUpdate(TS);
		for (auto const& Entity : this->_Entities)
		{
			Entity->OnUpdate(TS);
		}
	}

	void Scene::EventCallback(Event* E)
	{
		this->OnEvent(E);
		for (auto const& Entity : this->_Entities)
		{
			Entity->OnEvent(E);
		}
	}

	Scene::Scene()
	{
		VOLUND_INFO("Initializing Scene...");
	}

	Scene::~Scene()
	{

	}
}