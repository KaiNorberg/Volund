#include "PCH/PCH.h"

#include "Scene.h"

#include "Window/Window.h"

#include "Component/Components.h"

namespace Volund
{
	CHRONO_TIME_POINT Scene::GetStartTime()
	{
		return this->m_StartTime;
	}

	Entity Scene::RegisterNewEntity()
	{
		Entity newEntity = this->m_NewEntity;

		this->m_Registry.push_back(std::pair<Entity, PolyContainer<Component>>(newEntity, PolyContainer<Component>()));

		this->m_NewEntity++;
		return newEntity;
	}

	void Scene::UnregisterEntity(Entity entity)
	{
		const uint64_t index = FindEntity(entity);

		if (index != -1)
		{
			this->m_Registry.erase(this->m_Registry.begin() + index);
		}
		else
		{
			VOLUND_ERROR("Unable to find entity (%d)", entity);
		}
	}

	bool Scene::IsEntityRegistered(Entity entity)
	{
		return FindEntity(entity) != -1;
	}

	std::vector<Entity> Scene::GetRegisteredEntities()
	{
		std::vector<Entity> output;
		output.reserve(this->m_Registry.size());
		
		for (auto& [entity, polyContainer] : this->m_Registry)
		{
			output.push_back(entity);
		}

		return output;
	}

	void Scene::Procedure(const Event& e)
	{
		for (const auto& [entity, polystorage] : this->m_Registry)
		{
			for (auto& [typeID, components] : polystorage)
			{
				for (const auto& component : components)
				{
					component->Procedure(e);
				}
			}
		}
	}

	EntityRegistry::iterator Scene::begin()
	{
		return this->m_Registry.begin();
	}

	EntityRegistry::iterator Scene::end()
	{
		return this->m_Registry.end();
	}

	Scene::Scene()
	{
		this->m_StartTime = std::chrono::high_resolution_clock::now();
	}

	Scene::~Scene()
	{
		for (const auto& [entity, PolyContainer] : this->m_Registry)
		{
			for (auto& [TypeID, Components] : PolyContainer)
			{
				for (const auto& component : Components)
				{
					component->OnDestroy();
				}
			}
		}
	}

	uint64_t Scene::FindEntity(Entity entity)
	{
		VOLUND_PROFILE_FUNCTION();

		auto it = std::lower_bound(this->m_Registry.begin(), this->m_Registry.end(), entity, [](const std::pair<Entity, PolyContainer<Component>>& a, Entity entity)
		{
			return a.first < entity;
		});

		if (it != this->m_Registry.end())
		{
			return it - this->m_Registry.begin();
		}
		else
		{
			return -1;
		}
	}
}
