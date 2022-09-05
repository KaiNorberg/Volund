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

		template<typename T>
		uint32_t ComponentAmount();

		template<typename T>
		std::vector<Ref<Component>> const& ComponentView();

		void OnEvent(Event* E);

		void OnUpdate(TimeStep TS);

		Entity() = default;

		Entity(Scene* Parent, std::string const& Name = "");

		~Entity();

	private:

		Scene* _Parent;

		std::string _Name;

		static inline uint32_t _NewTypeID = 0;

		template<typename T>
		uint32_t GetTypeID();

		std::vector<std::vector<Ref<Component>>> _Components;
	};	

	template<typename T, class... ARGS>
	inline Ref<T> Entity::CreateComponent(ARGS&&... Args)
	{
		static uint64_t TypeID = GetTypeID<T>();

		while (this->_Components.size() <= TypeID)
		{
			this->_Components.push_back(std::vector<Ref<Component>>());
		}

		Ref<T> NewComponent = Ref<T>(new T(Args...));
		NewComponent->SetParent(this);
		NewComponent->OnCreate();
		this->_Components[TypeID].push_back(NewComponent);

		return NewComponent;
	}

	template<typename T>
	inline bool Entity::DeleteComponent(uint32_t Index)
	{
		static uint64_t TypeID = GetTypeID<T>();

		if (!this->HasComponent<T>(Index))
		{
			VOLUND_WARNING("Cant remove a component from a entity without that component.");
			return false;
		}

		this->_Components[TypeID][Index]->OnDelete();
		delete this->_Components[TypeID][Index];
		this->_Components[TypeID].erase(Index);

		return true;
	}

	template<typename T>
	inline Ref<T> Entity::GetComponent(uint32_t Index)
	{
		static uint64_t TypeID = GetTypeID<T>();

		if (!this->HasComponent<T>(Index))
		{
			VOLUND_WARNING("Cant get a component from a entity without that component.");
			return nullptr;
		}

		return std::dynamic_pointer_cast<T>(this->_Components[TypeID][Index]);
	}

	template<typename T>
	inline bool Entity::HasComponent(uint32_t Index)
	{
		static uint64_t TypeID = GetTypeID<T>();

		return TypeID < this->_Components.size() && Index < this->_Components[TypeID].size();
	}


	template<typename T>
	inline uint32_t Entity::ComponentAmount()
	{
		static uint64_t TypeID = GetTypeID<T>();
		
		if (TypeID < this->_Components.size())
		{
			return 0;
		}

		return this->_Components[TypeID].size();
	}

	template<typename T>
	inline std::vector<Ref<Component>> const& Entity::ComponentView()
	{
		static uint64_t TypeID = GetTypeID<T>();

		return this->_Components[TypeID];
	}

	template<typename T>
	inline uint32_t Entity::GetTypeID()
	{
		static uint32_t ID = _NewTypeID++;
		return ID;
	}
}

