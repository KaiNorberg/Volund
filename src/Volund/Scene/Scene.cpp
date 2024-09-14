#include "PCH/PCH.h"

#include "Scene.h"

#include "Window/Window.h"

#include "Component/Components.h"

namespace Volund
{
	std::vector<Scene::ComponentEntry>::iterator Scene::EntityEntry::begin()
	{
		return this->Components.begin();
	}

	std::vector<Scene::ComponentEntry>::iterator Scene::EntityEntry::end()
	{
		return this->Components.end();
	}

	CHRONO_TIME_POINT Scene::GetStartTime()
	{
		return this->m_StartTime;
	}

	Entity Scene::AllocateEntity()
	{
		uint32_t newEntityId = rand();

		if (!this->m_FreeEntries.empty())
		{
			uint32_t freeIndex = this->m_FreeEntries.back();
			EntityEntry& bucket = this->m_EntityHeap[freeIndex];
			this->m_FreeEntries.pop_back();

			bucket.entity = VOLUND_ENTITY_CREATE(newEntityId, freeIndex);
			return bucket.entity;
		}

		EntityEntry bucket;
		bucket.entity = VOLUND_ENTITY_CREATE(newEntityId, this->m_EntityHeap.size());

		this->m_EntityHeap.push_back(bucket);

		return bucket.entity;
	}

	void Scene::DeallocateEntity(Entity entity)
	{
		if (!IsAllocated(entity))
		{
			VOLUND_ERROR("Attempted to deallocate unallocated entity!");
		}

		uint64_t entityIndex = VOLUND_ENTITY_GET_INDEX(entity);

		this->m_EntityHeap[entityIndex].entity = VOLUND_NULL_ENTITY;
		this->m_EntityHeap[entityIndex].Components.clear();
		m_FreeEntries.push_back(entityIndex);

		while (!this->m_EntityHeap.empty() && this->m_EntityHeap.back().entity == VOLUND_NULL_ENTITY)
		{
			this->m_EntityHeap.pop_back();
			auto it = std::find(this->m_FreeEntries.begin(), this->m_FreeEntries.end(), this->m_EntityHeap.size() - 1);
			if (it != this->m_FreeEntries.end())
			{
				this->m_FreeEntries.erase(it);
			}
		}
	}

	bool Scene::IsAllocated(Entity entity)
	{
		uint64_t entityIndex = VOLUND_ENTITY_GET_INDEX(entity);

		return this->m_EntityHeap.size() > entityIndex && this->m_EntityHeap[entityIndex].entity != VOLUND_NULL_ENTITY;
	}

	void Scene::Procedure(const Event& e)
	{
		for (auto& entry : this->m_EntityHeap)
		{
			for (auto& [typeId, component] : entry)
			{
				component->Procedure(e);
			}
		}
	}

	std::vector<Scene::EntityEntry>::iterator Scene::begin()
	{
		return this->m_EntityHeap.begin();
	}

	std::vector<Scene::EntityEntry>::iterator Scene::end()
	{
		return this->m_EntityHeap.end();
	}

	std::vector<Scene::ComponentEntry>::iterator Scene::LowerBound(std::vector<ComponentEntry>& components, const size_t& typeId)
	{
		return std::lower_bound(components.begin(), components.end(), typeId);
	}

	std::vector<Scene::ComponentEntry>::iterator Scene::UpperBound(std::vector<ComponentEntry>& components, const size_t& typeId)
	{
		return std::upper_bound(components.begin(), components.end(), typeId);
	}

	std::shared_ptr<Scene> Scene::Create()
	{
		return std::shared_ptr<Scene>(new Scene());
	}

	Scene::Scene()
	{
		this->m_StartTime = std::chrono::high_resolution_clock::now();
	}

	Scene::~Scene()
	{
		for (auto& entry : this->m_EntityHeap)
		{
			for (auto& [typeId, component] : entry)
			{
				component->OnDestroy();
			}
		}
		this->m_EntityHeap.clear();
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
