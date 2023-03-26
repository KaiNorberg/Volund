 #pragma once

#include "EventDispatcher/Event.h"
#include "Component/Component.h"
#include "Container/Container.h"

#include "Renderer/Framebuffer/Framebuffer.h"

#include "Input/Input.h"

namespace Volund
{
	using Entity = uint64_t;
	using Registry = std::vector<std::pair<Entity, Container<Component>>>;

	class Scene
	{
	public:

		std::chrono::time_point<std::chrono::steady_clock> GetStartTime();

		Ref<Framebuffer> GetTargetBuffer();

		Entity CreateEntity();
		void DestroyEntity(Entity entity);
		bool HasEntity(Entity entity);

		template <typename T>
		void DeleteComponent(Entity entity, uint64_t index = 0);
		template <typename T, typename... Args>
		Ref<T> CreateComponent(Entity entity, Args&&... args);
		template <typename T>
		bool HasComponent(Entity entity);	
		template <typename T>
		uint64_t ComponentAmount(Entity entity);
		template <typename T>
		Ref<T> GetComponent(Entity entity, uint64_t index = 0);

		template <typename T>
		void View(std::vector<Ref<T>>& output);

		void ResizeTarget(uint32_t width, uint32_t height);
		
		void Procedure(const Event& e);

		Registry::iterator begin();
		Registry::iterator end();

		Scene();

		~Scene();

	private:

		uint64_t FindEntity(Entity entity);

		uint64_t m_NewEntity = 1;

		Registry m_Registry;

		std::chrono::time_point<std::chrono::steady_clock> m_StartTime;

		Ref<Framebuffer> m_TargetBuffer;
	};

	template<typename T>
	inline void Scene::DeleteComponent(Entity entity, uint64_t index)
	{
		VOLUND_PROFILE_FUNCTION();

		const uint64_t entityIndex = FindEntity(entity);

		if (entityIndex != -1)
		{
			this->m_Registry[entityIndex].second.Get<T>(index)->OnDestroy();
			this->m_Registry[entityIndex].second.Erase<T>(index);
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
			this->m_Registry[index].second.PushBack(newComponent);

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

		return entityIndex != -1 && this->m_Registry[entityIndex].second.Contains<T>();
	}

	template<typename T>
	inline uint64_t Scene::ComponentAmount(Entity entity)
	{
		VOLUND_PROFILE_FUNCTION();

		const uint64_t entityIndex = FindEntity(entity);

		return entityIndex != -1 && this->m_Registry[entityIndex].second.Contains<T>() ? this->m_Registry[entityIndex].second.Size<T>() : 0;
	}

	template<typename T>
	inline Ref<T> Scene::GetComponent(Entity entity, uint64_t index)
	{
		VOLUND_PROFILE_FUNCTION();

		const uint64_t entityIndex = FindEntity(entity);

		return entityIndex != -1 && this->m_Registry[entityIndex].second.Contains<T>() ? this->m_Registry[entityIndex].second.Get<T>(index) : nullptr;
	}

	template<typename T>
	inline void Scene::View(std::vector<Ref<T>>& output)
	{
		VOLUND_PROFILE_FUNCTION();

		output.reserve(this->m_Registry.size());

		for (auto& [entity, Container] : this->m_Registry)
		{
			for (auto& component : Container.View<T>())
			{
				output.push_back(std::dynamic_pointer_cast<T>(component));
			}
		}
	}
}
