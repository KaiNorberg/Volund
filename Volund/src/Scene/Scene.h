#pragma once

#include "EventDispatcher/Event.h"
#include "Component/Component.h"
#include "Container/Container.h"

namespace Volund
{
	using Entity = uint64_t;
	using Registry = std::vector<std::pair<Entity, Container<Component>>>;

	class Scene
	{
	public:

		static std::string GetFilepath();

		static Entity CreateEntity();
		static void DestroyEntity(Entity entity);
		static bool HasEntity(Entity entity);

		static void DeleteComponent(Component* component);
		template <typename T>
		static void DeleteComponent(Entity entity, uint64_t Index = 0);
		template <typename T, class... ARGS>
		static Ref<T> CreateComponent(Entity entity, ARGS&&... Args);
		template <typename T>
		static bool HasComponent(Entity entity, uint64_t Index = 0);
		template <typename T>
		static Ref<T> GetComponent(Entity entity, uint64_t Index = 0);

		template <typename T>
		static const std::vector<Ref<Component>>& View(Entity entity);
		template <typename T>
		static std::vector<std::vector<Ref<Component>>> View();

		static void OnEvent(Event* E);
		static void OnUpdate(TimeStep TS);

		static Registry::iterator begin();
		static Registry::iterator end();

		static void Load(const std::string& Filepath);

	private:

		Scene() = default;

		static uint64_t FindEntity(Entity entity);

		static inline struct SceneData
		{
			Registry Registry;

			std::string Filepath;

			uint64_t NewEntity = 1;

		} _Data;
	};

	template<typename T>
	inline void Scene::DeleteComponent(Entity entity, uint64_t Index)
	{
		uint64_t EntityIndex = FindEntity(entity);

		if (EntityIndex != -1)
		{
			_Data.Registry[EntityIndex].second.Get<T>(Index)->OnDelete();
			_Data.Registry[EntityIndex].second.Erase<T>(Index);
		}
		else
		{
			VOLUND_ERROR("Unable to find entity (%d)", entity);
		}
	}

	template<typename T, class ...ARGS>
	inline Ref<T> Scene::CreateComponent(Entity entity, ARGS && ...Args)
	{
		uint64_t Index = FindEntity(entity);

		if (Index != -1)
		{
			Ref<T> NewComponent = std::make_shared<T>(Args...);
			NewComponent->Init(entity);
			NewComponent->OnCreate();
			_Data.Registry[Index].second.PushBack(NewComponent);

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
		uint64_t RegistryIndex = FindEntity(entity);

		if (RegistryIndex != -1)
		{
			return _Data.Registry[RegistryIndex].second.Contains<T>(Index);

		}
		else
		{
			return false;
		}
	}

	template<typename T>
	inline Ref<T> Scene::GetComponent(Entity entity, uint64_t Index)
	{
		uint64_t RegistryIndex = FindEntity(entity);

		if (RegistryIndex != -1)
		{
			return _Data.Registry[RegistryIndex].second.Get<T>(Index);

		}
		else
		{
			VOLUND_ERROR("Unable to find entity (%d)", entity);
			return nullptr;
		}
	}

	template<typename T>
	inline const std::vector<Ref<Component>>& Scene::View(Entity entity)
	{
		uint64_t Index = FindEntity(entity);

		if (Index != -1)
		{
			return _Data.Registry[Index].second.View<T>();
		}
		else
		{
			VOLUND_ERROR("Unable to find entity (%d)", entity);
			return _Data.Registry[Index].second.View<T>();
		}
	}

	template<typename T>
	inline std::vector<std::vector<Ref<Component>>> Scene::View()
	{
		std::vector<std::vector<Ref<Component>>> Return;

		for (auto& [Entity, View] : _Data.Registry)
		{
			if (View.Contains<T>())
			{
				Return.push_back(View.View<T>());
			}
		}

		return Return;
	}
}
