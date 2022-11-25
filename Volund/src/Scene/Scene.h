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

		Entity CreateEntity();

		void DestroyEntity(Entity entity);

		bool HasEntity(Entity entity) const;

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
		const std::vector<Ref<Component>>& View(Entity entity) const;

		template <typename T>
		std::vector<std::vector<Ref<Component>>> View() const;

		void OnEvent(Event* E);

		void OnUpdate(TimeStep TS);

		void Serialize(std::string_view Filepath);

		VML Serialize();

		Registry::iterator begin();
		Registry::iterator end();

		Registry::const_iterator begin() const;
		Registry::const_iterator end() const;

		Scene(std::string_view Filepath);

		~Scene();

	private:

		uint64_t FindEntity(Entity entity) const;

		uint64_t _NewEntity = 1;

		Registry _Registry;
	
		std::string Filepath;
	};

	template<typename T>
	inline void Scene::DeleteComponent(Entity entity, uint64_t Index)
	{
		uint64_t Index = this->FindEntity(entity);

		if (Index != -1)
		{
			this->_Registry[Index].second.Get<T>(Index)->OnDelete();
			this->_Registry[Index].second.Erase<T>(Index);
		}
		else
		{
			VOLUND_ERROR("Unable to find entity (%d)", entity);
		}
	}

	template<typename T, class ...ARGS>
	inline Ref<T> Scene::CreateComponent(Entity entity, ARGS && ...Args)
	{
		uint64_t Index = this->FindEntity(entity);

		if (Index != -1)
		{
			Ref<T> NewComponent = std::make_shared<T>(Args...);
			NewComponent->Init(this, entity);
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
		uint64_t RegistryIndex = this->FindEntity(entity);

		if (RegistryIndex != -1)
		{
			return this->_Registry[RegistryIndex].second.Contains<T>(Index);

		}
		else
		{
			return false;
		}
	}

	template<typename T>
	inline Ref<T> Scene::GetComponent(Entity entity, uint64_t Index)
	{
		uint64_t RegistryIndex = this->FindEntity(entity);

		if (RegistryIndex != -1)
		{
			return this->_Registry[RegistryIndex].second.Get<T>(Index);

		}
		else
		{
			VOLUND_ERROR("Unable to find entity (%d)", entity);
			return nullptr;
		}
	}

	template<typename T>
	inline const std::vector<Ref<Component>>& Scene::View(Entity entity) const
	{
		uint64_t Index = this->FindEntity(entity);

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
	inline std::vector<std::vector<Ref<Component>>> Scene::View() const
	{
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
