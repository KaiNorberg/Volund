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

		std::chrono::time_point<std::chrono::steady_clock> GetStartTime();

		Ref<Framebuffer> GetTargetBuffer();

		Entity CreateEntity();
		void DestroyEntity(Entity entity);
		bool HasEntity(Entity entity);

		template <typename T>
		void DeleteComponent(Entity entity, uint64_t Index = 0);
		template <typename T, class... ARGS>
		Ref<T> CreateComponent(Entity entity, ARGS&&... Args);
		template <typename T>
		bool HasComponent(Entity entity);	
		template <typename T>
		uint64_t ComponentAmount(Entity entity);
		template <typename T>
		Ref<T> GetComponent(Entity entity, uint64_t Index = 0);

		template <typename T>
		void View(std::vector<Ref<T>>& Output);

		void ResizeTarget(uint32_t Width, uint32_t Height);
		
		void Procedure(const Event& E);

		Registry::iterator begin();
		Registry::iterator end();

		Scene();

		~Scene();

	private:

		uint64_t FindEntity(Entity entity);

		uint64_t _NewEntity = 1;

		Registry _Registry;

		std::chrono::time_point<std::chrono::steady_clock> _StartTime;

		Ref<Framebuffer> _TargetBuffer;
	};

	template<typename T>
	inline void Scene::DeleteComponent(Entity entity, uint64_t Index)
	{
		VOLUND_PROFILE_FUNCTION();

		uint64_t EntityIndex = FindEntity(entity);

		if (EntityIndex != -1)
		{
			this->_Registry[EntityIndex].second.Get<T>(Index)->OnDestroy();
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
	inline bool Scene::HasComponent(Entity entity)
	{
		VOLUND_PROFILE_FUNCTION();

		uint64_t EntityIndex = FindEntity(entity);

		return EntityIndex != -1 && this->_Registry[EntityIndex].second.Contains<T>();
	}

	template<typename T>
	inline uint64_t Scene::ComponentAmount(Entity entity)
	{
		VOLUND_PROFILE_FUNCTION();

		uint64_t EntityIndex = FindEntity(entity);

		return EntityIndex != -1 && this->_Registry[EntityIndex].second.Contains<T>() ? this->_Registry[EntityIndex].second.Size<T>() : 0;
	}

	template<typename T>
	inline Ref<T> Scene::GetComponent(Entity entity, uint64_t Index)
	{
		VOLUND_PROFILE_FUNCTION();

		uint64_t EntityIndex = FindEntity(entity);

		return EntityIndex != -1 && this->_Registry[EntityIndex].second.Contains<T>() ? this->_Registry[EntityIndex].second.Get<T>(Index) : nullptr;
	}

	template<typename T>
	inline void Scene::View(std::vector<Ref<T>>& Output)
	{
		VOLUND_PROFILE_FUNCTION();

		Output.reserve(this->_Registry.size());

		for (auto& [entity, Container] : this->_Registry)
		{
			for (auto& component : Container.View<T>())
			{
				Output.push_back(std::dynamic_pointer_cast<T>(component));
			}
		}
	}
}
