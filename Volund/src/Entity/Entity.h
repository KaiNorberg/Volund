#pragma once

#include "Component/Component.h"

namespace Volund
{
	class Scene;

	class Entity
	{
	public:
	
		std::string GetName();

		Scene* GetParent();

		template<typename T, class... ARGS>
		Ref<T> CreateComponent(ARGS&&... Args);

		template<typename T>
		bool DeleteComponent(uint32_t Index = 0);

		template<typename T>
		Ref<T> GetComponent(uint32_t Index = 0);

		template<typename T>
		bool HasComponent(uint32_t Index = 0);

		void OnEvent(Event* E);

		void OnUpdate(TimeStep TS);

		Entity() = default;

		Entity(Scene* Parent, std::string const& Name = "");

		~Entity();

	private:

		Scene* _Parent;

		std::string _Name;

		std::unordered_map<uint64_t, std::vector<Ref<Component>>> _Components;
	};	

	template<typename T, class... ARGS>
	Ref<T> Entity::CreateComponent(ARGS&&... Args)
	{
		uint64_t Hash = typeid(T).hash_code();

		Ref<T> NewComponent = Ref<T>(new T(Args...));
		NewComponent->SetParent(this);
		NewComponent->OnCreate();
		this->_Components[Hash].push_back(NewComponent);

		return NewComponent;
	}

	template<typename T>
	bool Entity::DeleteComponent(uint32_t Index)
	{
		if (!this->HasComponent<T>(Index))
		{
			VOLUND_WARNING("Cant remove a component from a entity without that component.");
			return false;
		}

		uint64_t Hash = typeid(T).hash_code();
		this->_Components[Hash][Index]->OnDelete();
		delete this->_Components[Hash][Index];
		this->_Components[Hash].erase(Index);

		return true;
	}

	template<typename T>
	Ref<T> Entity::GetComponent(uint32_t Index)
	{
		if (!this->HasComponent<T>(Index))
		{
			VOLUND_WARNING("Cant get a component from a entity without that component.");
			return nullptr;
		}

		uint64_t Hash = typeid(T).hash_code();
		return std::dynamic_pointer_cast<T>(this->_Components[Hash][Index]);
	}

	template<typename T>
	bool Entity::HasComponent(uint32_t Index)
	{
		uint64_t Hash = typeid(T).hash_code();
		return this->_Components.find(Hash) != this->_Components.end() && Index < this->_Components[Hash].size();
	}
}

