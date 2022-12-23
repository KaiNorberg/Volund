#pragma once

#include "EventDispatcher/Event.h"
#include "Component/Component.h"
#include "Container/Container.h"

#include "Renderer/Framebuffer/Framebuffer.h"

#include "Input/Input.h"

#include "Lua/LuaState/LuaState.h"

namespace Volund
{
	using Entity = uint64_t;
	using Registry = std::vector<std::pair<Entity, Container<Component>>>;

	class Scene
	{
	public:

		Ref<Framebuffer> GetTargetBuffer();

		Entity CreateEntity();
		void DestroyEntity(Entity entity);
		bool HasEntity(Entity entity);

		void DeleteComponent(Component* component);
		template <typename T>
		void DeleteComponent(Entity entity, uint64_t Index = 0);
		template <typename T, class... ARGS>
		Ref<T> CreateComponent(Entity entity, ARGS&&... Args);
		template <typename T>
		bool HasComponent(Entity entity, uint64_t Index = 0);
		template <typename T>
		Ref<T> GetComponent(Entity entity, uint64_t Index = 0);

		template <typename T>
		const std::vector<Ref<Component>>& View(Entity entity);
		template <typename T>
		std::vector<std::vector<Ref<Component>>> View();

		void ResizeTarget(uint32_t Width, uint32_t Height);
		
		void OnEvent(Event* E);
		void OnUpdate(TimeStep TS);
		void OnRender();

		Registry::iterator begin();
		Registry::iterator end();

		Scene();

		~Scene();

	private:

		uint64_t FindEntity(Entity entity);

		uint64_t _NewEntity = 1;

		Registry _Registry;

		Ref<Framebuffer> _TargetBuffer;
	};

	template<typename T>
	inline void Scene::DeleteComponent(Entity entity, uint64_t Index)
	{
		VOLUND_PROFILE_FUNCTION();

		uint64_t EntityIndex = FindEntity(entity);

		if (EntityIndex != -1)
		{
			this->_Registry[EntityIndex].second.Get<T>(Index)->OnDelete();
			this->_Registry[EntityIndex].second.Erase<T>(Index);
		}
		else
		{
			VOLUND_ERROR("Unable to find entity (%d)", entity);
		}
	}

	template<typename T, class ...ARGS>
	inline Ref<T> Scene::CreateComponent(Entity entity, ARGS && ...Args)
	{
		VOLUND_PROFILE_FUNCTION();

		uint64_t Index = FindEntity(entity);

		if (Index != -1)
		{
			Ref<T> NewComponent = std::make_shared<T>(Args...);
			NewComponent->Init(entity, this);
			NewComponent->OnCreate();
			this->_Registry[Index].second.PushBack(NewComponent);

			return NewComponent;
		}
		else
		{
			VOLUND_ERROR("Unable to find entity (%d)", entity);
			return nullptr;
		}
	}

	template<typename T>
	inline bool Scene::HasComponent(Entity entity, uint64_t Index)
	{
		VOLUND_PROFILE_FUNCTION();

		uint64_t RegistryIndex = FindEntity(entity);

		return RegistryIndex != -1 && this->_Registry[RegistryIndex].second.Contains<T>(Index);
	}

	template<typename T>
	inline Ref<T> Scene::GetComponent(Entity entity, uint64_t Index)
	{
		VOLUND_PROFILE_FUNCTION();

		uint64_t RegistryIndex = FindEntity(entity);

		return RegistryIndex != -1 && this->_Registry[RegistryIndex].second.Contains<T>(Index) ? this->_Registry[RegistryIndex].second.Get<T>(Index) : nullptr;
	}

	template<typename T>
	inline const std::vector<Ref<Component>>& Scene::View(Entity entity)
	{
		VOLUND_PROFILE_FUNCTION();

		uint64_t Index = FindEntity(entity);

		if (Index != -1)
		{
			return this->_Registry[Index].second.View<T>();
		}
		else
		{
			VOLUND_ERROR("Unable to find entity (%d)", entity);
			return this->_Registry[Index].second.View<T>();
		}
	}

	template<typename T>
	inline std::vector<std::vector<Ref<Component>>> Scene::View()
	{
		VOLUND_PROFILE_FUNCTION();

		std::vector<std::vector<Ref<Component>>> Return;

		for (auto& [Entity, View] : this->_Registry)
		{
			if (View.Contains<T>())
			{
				Return.push_back(View.View<T>());
			}
		}

		return Return;
	}
}
