 #pragma once

#include "Dispatcher/Event/Event.h"
#include "Component/Component.h"
#include "PolyContainer/PolyContainer.h"

#include "Rendering/Framebuffer/Framebuffer.h"

#include "Input/Input.h"

namespace Volund
{
	using Entity = uint64_t;

	struct RegistryEntry
	{
		Entity entity;
		PolyContainer<Component> componentContainer;

		RegistryEntry(Entity entityId);
	};

	using EntityRegistry = std::vector<RegistryEntry>;

	class Scene
	{
	public:

		CHRONO_TIME_POINT GetStartTime();

		Entity RegisterNewEntity();

		void UnregisterEntity(Entity entity);

		bool IsEntityRegistered(Entity entity);

		std::vector<Entity> GetRegisteredEntities();

		template<typename T>
		void DeleteComponent(Entity entity, uint64_t index = 0);

		template<typename T, typename... Args>
		Ref<T> CreateComponent(Entity entity, Args&&... args);

		template<typename T>
		bool HasComponent(Entity entity);	

		template<typename T>
		uint64_t ComponentAmount(Entity entity);

		template<typename T>
		Ref<T> GetComponent(Entity entity, uint64_t index = 0);
		
		void Procedure(const Event& e);

		EntityRegistry::iterator begin();
		EntityRegistry::iterator end();

		Scene();

		~Scene();

	private:

		uint64_t FindEntity(Entity entity);

		uint64_t m_NewEntity = 1;

		EntityRegistry m_Registry;
		
		CHRONO_TIME_POINT m_StartTime;
	};

    template <typename T>
    inline void Scene::DeleteComponent(Entity entity, uint64_t index)
    {
		VOLUND_PROFILE_FUNCTION();

		const uint64_t entityIndex = FindEntity(entity);

		if (entityIndex != -1)
		{
			this->m_Registry[entityIndex].componentContainer.Get<T>(index)->OnDestroy();
			this->m_Registry[entityIndex].componentContainer.Erase<T>(index);
		}
		else
		{
			VOLUND_ERROR("Unable to find entity (%d)", entity);
		}
	}

	template<typename T, typename ...Args>
	inline Ref<T> Scene::CreateComponent(Entity entity, Args && ...args)
	{
		VOLUND_PROFILE_FUNCTION();

		const uint64_t index = FindEntity(entity);

		if (index != -1)
		{
			Ref<T> newComponent = std::make_shared<T>(args...);
			newComponent->Init(entity, this);
			newComponent->OnCreate();
			this->m_Registry[index].componentContainer.PushBack(newComponent);

			return newComponent;
		}
		else
		{
			VOLUND_ERROR("Unable to find entity (%d)", entity);
			return nullptr;
		}
	}

	template<typename T>
	inline bool Scene::HasComponent(Entity entity)
	{
		VOLUND_PROFILE_FUNCTION();

		const uint64_t entityIndex = FindEntity(entity);

		return entityIndex != -1 && this->m_Registry[entityIndex].componentContainer.Contains<T>();
	}

	template<typename T>
	inline uint64_t Scene::ComponentAmount(Entity entity)
	{
		VOLUND_PROFILE_FUNCTION();

		const uint64_t entityIndex = FindEntity(entity);

		return entityIndex != -1 && this->m_Registry[entityIndex].componentContainer.Contains<T>() ? this->m_Registry[entityIndex].componentContainer.Size<T>() : 0;
	}

	template<typename T>
	inline Ref<T> Scene::GetComponent(Entity entity, uint64_t index)
	{
		VOLUND_PROFILE_FUNCTION();

		const uint64_t entityIndex = FindEntity(entity);

		return entityIndex != -1 && this->m_Registry[entityIndex].componentContainer.Contains<T>() ? this->m_Registry[entityIndex].componentContainer.Get<T>(index) : nullptr;
	}
}
