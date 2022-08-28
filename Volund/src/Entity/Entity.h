#pragma once

#include "Component/Components.h"

namespace Volund
{
	class Scene;

	class Entity
	{
	public:
	
		std::string GetName();

		Scene* GetParent();

		template<typename T, class... ARGS>
		T* AddComponent(ARGS&&... Args);

		template<typename T>
		bool RemoveComponent(uint32_t Index = 0);

		template<typename T>
		T* GetComponent(uint32_t Index = 0);

		template<typename T>
		bool HasComponent(uint32_t Index = 0) const;

		void OnUpdate(TimeStep TS);

		Entity() = default;

		Entity(Scene* Parent, std::string const& Name = "");

		~Entity();

	private:

		Scene* _Parent;

		std::string _Name;

		std::unordered_map<uint64_t, std::vector<Component*>> _Components;
	};	

	template<typename T, class... ARGS>
	T* Entity::AddComponent(ARGS&&... Args)
	{
		uint64_t Hash = typeid(T).hash_code();

		if (!this->HasComponent<T>())
		{
			this->_Components[Hash] = std::vector<Component*>();
		}

		T* NewComponent = new T(Args...);
		this->_Components[Hash].push_back(NewComponent);

		return NewComponent;
	}

	template<typename T>
	bool Entity::RemoveComponent(uint32_t Index)
	{
		if (!this->HasComponent<T>(Index))
		{
			VOLUND_WARNING("Cant remove a component from a entity without that component.");
			return false;
		}

		uint64_t Hash = typeid(T).hash_code();
		delete this->_Components[Hash][Index];
		this->_Components[Hash].erase(Index);

		return true;
	}

	template<typename T>
	T* Entity::GetComponent(uint32_t Index)
	{
		if (!this->HasComponent<T>(Index))
		{
			VOLUND_WARNING("Cant get a component from a entity without that component.");
			return nullptr;
		}

		uint64_t Hash = typeid(T).hash_code();
		return this->_Components[Hash][Index];
	}

	template<typename T>
	bool Entity::HasComponent(uint32_t Index) const
	{
		uint64_t Hash = typeid(T).hash_code();
		return this->_Components.find(Hash) != this->_Components.end() && Index < this->_Components[Hash].size();
	}
}

