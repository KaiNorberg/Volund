
#include "Scene.h"

#include "Window.h"

#include "Component/Components.h"

namespace Volund
{
	std::vector<Scene::ComponentEntry>::iterator Scene::EntityEntry::begin()
	{
		return this->components.begin();
	}

	std::vector<Scene::ComponentEntry>::iterator Scene::EntityEntry::end()
	{
		return this->components.end();
	}

	CHRONO_TIME_POINT Scene::GetStartTime()
	{
		return this->m_startTime;
	}

	Entity Scene::Register()
	{
		uint32_t newEntityId = rand();

		if (!this->m_freeEntries.empty())
		{
			uint32_t freeIndex = this->m_freeEntries.back();
			EntityEntry& bucket = this->m_entityHeap[freeIndex];
			this->m_freeEntries.pop_back();

			bucket.entity = VOLUND_ENTITY_CREATE(newEntityId, freeIndex);
			return bucket.entity;
		}

		EntityEntry bucket;
		bucket.entity = VOLUND_ENTITY_CREATE(newEntityId, this->m_entityHeap.size());

		this->m_entityHeap.push_back(bucket);

		return bucket.entity;
	}

	void Scene::Unregister(Entity entity)
	{
		if (!IsRegistered(entity))
		{
			VOLUND_ERROR("Attempted to unregister unregistered entity!");
		}

		uint64_t entityIndex = VOLUND_ENTITY_GET_INDEX(entity);

		this->m_entityHeap[entityIndex].entity = VOLUND_ENTITY_NULL;
		this->m_entityHeap[entityIndex].components.clear();
		m_freeEntries.push_back(entityIndex);

		while (!this->m_entityHeap.empty() && this->m_entityHeap.back().entity == VOLUND_ENTITY_NULL)
		{
			this->m_entityHeap.pop_back();
			auto it = std::find(this->m_freeEntries.begin(), this->m_freeEntries.end(), this->m_entityHeap.size() - 1);
			if (it != this->m_freeEntries.end())
			{
				this->m_freeEntries.erase(it);
			}
		}
	}

	bool Scene::IsRegistered(Entity entity)
	{
		uint64_t entityIndex = VOLUND_ENTITY_GET_INDEX(entity);

		return this->m_entityHeap.size() > entityIndex && this->m_entityHeap[entityIndex].entity != VOLUND_ENTITY_NULL;
	}

	void Scene::Procedure(const Event& e)
	{
		for (auto& entry : this->m_entityHeap)
		{
			for (auto& [typeId, component] : entry)
			{
				component->Procedure(e);
			}
		}
	}

	std::vector<Scene::EntityEntry>::iterator Scene::begin()
	{
		return this->m_entityHeap.begin();
	}

	std::vector<Scene::EntityEntry>::iterator Scene::end()
	{
		return this->m_entityHeap.end();
	}

	std::vector<Scene::ComponentEntry>::iterator Scene::LowerBound(std::vector<ComponentEntry>& components, const size_t& typeId)
	{
		return std::lower_bound(components.begin(), components.end(), typeId);
	}

	std::vector<Scene::ComponentEntry>::iterator Scene::UpperBound(std::vector<ComponentEntry>& components, const size_t& typeId)
	{
		return std::upper_bound(components.begin(), components.end(), typeId);
	}

	Scene::Scene()
	{
		this->m_startTime = std::chrono::high_resolution_clock::now();
	}

	Scene::~Scene()
	{
		for (auto& entry : this->m_entityHeap)
		{
			for (auto& [typeId, component] : entry)
			{
				component->OnDestroy();
			}
		}
		this->m_entityHeap.clear();
	}

	bool operator<(const size_t& a, const Scene::ComponentEntry& b)
	{
		return a < b.TypeId;
	}

	bool operator<(const Scene::ComponentEntry& a, const size_t& b)
	{
		return a.TypeId < b;
	}
}
