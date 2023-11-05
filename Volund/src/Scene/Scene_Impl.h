#pragma once

namespace Volund
{
	template<typename T>
	inline bool Scene::ComponentEntry::Is()
	{
		return this->TypeId == Utils::GetTypeId<T>();
	}

	template<typename T>
	inline Ref<T> Scene::ComponentEntry::As()
	{
		return std::dynamic_pointer_cast<T>(this->component);
	}

	template<typename T, typename ...Args>
	inline Ref<T> Scene::CreateComponent(Entity entity, Args && ...args)
	{
		VOLUND_PROFILE_FUNCTION();

		if (!IsAllocated(entity))
		{
			VOLUND_ERROR("Unallocated entity detected!");
		}

		uint64_t entityIndex = VOLUND_ENTITY_GET_INDEX(entity);
		auto& entry = this->m_EntityHeap[entityIndex];

		Ref<T> newComponent = std::make_shared<T>(args...);
		newComponent->Init(entity, this);
		newComponent->OnCreate();

		size_t componentTypeId = Utils::GetTypeId<T>();

		auto insertPos = UpperBound(entry.Components, componentTypeId);
		ComponentEntry newEntry = ComponentEntry(Utils::GetTypeId<T>(), newComponent);
		entry.Components.insert(insertPos, newEntry);

		return newComponent;
	}

	template <typename T>
	inline void Scene::DeleteComponent(Entity entity, uint64_t index)
	{
		VOLUND_PROFILE_FUNCTION();

		if (!IsAllocated(entity))
		{
			VOLUND_ERROR("Unallocated entity detected!");
		}

		uint64_t entityIndex = VOLUND_ENTITY_GET_INDEX(entity);
		auto& entry = this->m_EntityHeap[entityIndex];

		size_t componentTypeId = Utils::GetTypeId<T>();

		auto componentEntry = LowerBound(entry.Components, componentTypeId) + index;

		if (componentEntry < entry.Components.end() && (*componentEntry).TypeId == componentTypeId)
		{
			entry.Components.erase(componentEntry);
		}
		else
		{
			VOLUND_ERROR("Component out of bounds!");
		}
	}

	template<typename T>
	inline bool Scene::HasComponent(Entity entity, uint64_t index)
	{
		VOLUND_PROFILE_FUNCTION();

		if (!IsAllocated(entity))
		{
			return false;
		}

		uint64_t entityIndex = VOLUND_ENTITY_GET_INDEX(entity);
		auto& entry = this->m_EntityHeap[entityIndex];

		size_t componentTypeId = Utils::GetTypeId<T>();

		auto componentEntry = LowerBound(entry.Components, componentTypeId) + index;

		return componentEntry < entry.Components.end() && (*componentEntry).TypeId == componentTypeId;
	}

	template<typename T>
	inline uint64_t Scene::ComponentAmount(Entity entity)
	{
		VOLUND_PROFILE_FUNCTION();

		if (!IsAllocated(entity))
		{
			return false;
		}

		uint64_t entityIndex = VOLUND_ENTITY_GET_INDEX(entity);
		auto& entry = this->m_EntityHeap[entityIndex];

		size_t componentTypeId = Utils::GetTypeId<T>();

		auto lower = LowerBound(entry.Components, componentTypeId);
		auto upper = UpperBound(entry.Components, componentTypeId);

		return upper - lower;
	}

	template<typename T>
	inline Ref<T> Scene::GetComponent(Entity entity, uint64_t index)
	{
		VOLUND_PROFILE_FUNCTION();

		if (!IsAllocated(entity))
		{
			VOLUND_ERROR("Unallocated entity detected!");
		}

		uint64_t entityIndex = VOLUND_ENTITY_GET_INDEX(entity);
		auto& entry = this->m_EntityHeap[entityIndex];

		size_t componentTypeId = Utils::GetTypeId<T>();

		auto componentEntry = LowerBound(entry.Components, componentTypeId) + index;

		if (componentEntry < entry.Components.end() && (*componentEntry).TypeId == componentTypeId)
		{
			return (*componentEntry).As<T>();
		}
		else
		{
			VOLUND_ERROR("Component out of bounds!");
			return nullptr;
		}
	}
}