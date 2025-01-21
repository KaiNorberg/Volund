
#include "Scene.h"

#include "Window.h"

#include "Component/Components.h"

namespace Volund
{
	std::vector<Scene::ComponentEntry>::iterator Scene::EntityRecord::begin()
	{
		return this->m_components.begin();
	}

	std::vector<Scene::ComponentEntry>::iterator Scene::EntityRecord::end()
	{
		return this->m_components.end();
	}

    std::vector<Scene::ComponentEntry>::iterator Scene::EntityRecord::Find(uint64_t typeId, uint64_t index)
	{
		auto it = std::lower_bound(this->m_components.begin(), this->m_components.end(), typeId,
		[](const ComponentEntry& entry, uint64_t type) {
			return entry.GetTypeId() < type;
		});
		
		while (index > 0 && it != m_components.end() && it->GetTypeId() == typeId)
		{
			++it;
			--index;
		}
		
		if (it != m_components.end() && it->GetTypeId() == typeId)
		{
			return it;
		}
		
    	return this->m_components.end();
	}

	CHRONO_TIME_POINT Scene::GetStartTime()
	{
		return this->m_startTime;
	}

	Entity Scene::Register()
	{
		for (uint64_t i = 0; i < this->m_indirectionTable.size(); i++)
		{
			if (this->m_indirectionTable[i].avail)
			{		
				Entity entity;
				entity.index = i;
				entity.generation = this->m_newGeneration++;

				this->m_entites.push_back(EntityRecord(entity));
				this->m_indirectionTable[i].recordIndex = this->m_entites.size() - 1;
				this->m_indirectionTable[i].generation = entity.generation;
				this->m_indirectionTable[i].avail = false;

				return entity;
			}
		}

		Entity entity;
		entity.index = this->m_indirectionTable.size();
		entity.generation = this->m_newGeneration++;
		
		this->m_entites.push_back(EntityRecord(entity));
		this->m_indirectionTable.push_back((IndirectionEntry){this->m_entites.size() - 1, entity.generation, false});
		return entity;
	}

	void Scene::Unregister(Entity entity)
	{
		if (!IsRegistered(entity))
		{
			VOLUND_ERROR("Attempted to unregister unregistered entity!");
		}

    	uint64_t recordIndex = this->m_indirectionTable[entity.index].recordIndex;

		if (recordIndex < this->m_entites.size() - 1)
		{
			this->m_entites[recordIndex] = std::move(m_entites.back());
			this->m_indirectionTable[this->m_entites[recordIndex].m_entity.index].recordIndex = recordIndex;
		}
		
		this->m_entites.pop_back();
		this->m_indirectionTable[entity.index].avail = true;
	}

	bool Scene::IsRegistered(Entity entity)
	{
    	return entity.index < m_indirectionTable.size() && entity.generation == m_indirectionTable[entity.index].generation && !m_indirectionTable[entity.index].avail;	
	}

	void Scene::Procedure(const Event& e)
	{
		for (auto& entity : this->m_entites)
		{
			for (auto& [typeId, component] : entity)
			{
				component->Procedure(e);
			}
		}
	}

	std::vector<Scene::EntityRecord>::iterator Scene::begin()
	{
		return this->m_entites.begin();
	}

	std::vector<Scene::EntityRecord>::iterator Scene::end()
	{
		return this->m_entites.end();
	}

	Scene::Scene()
	{
		this->m_startTime = std::chrono::high_resolution_clock::now();
	}

	Scene::~Scene()
	{
		this->m_entites.clear();
	}

	bool operator<(const size_t& a, const Scene::ComponentEntry& b)
	{
		return a < b.GetTypeId();
	}

	bool operator<(const Scene::ComponentEntry& a, const size_t& b)
	{
		return a.GetTypeId() < b;
	}
}
