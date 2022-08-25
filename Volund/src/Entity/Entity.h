#pragma once

#include "Component/SimpleComponent.h"
#include "Component/NativeComponents/NativeComponents.h"

namespace Volund
{
	class Scene;

	class Entity
	{
	public:
	
		Scene* GetParent();

		std::string GetName();

		bool Error();

		SimpleComponent* AddComponent(JSON ComponentJSON);

		bool RemoveComponent(std::string const& Type);

		SimpleComponent* GetComponent(std::string const& Type);

		bool HasComponent(std::string const& Type) const;

		template<typename T>
		bool RemoveComponent();

		template<typename T>
		T* GetComponent();

		template<typename T>
		bool HasComponent() const;

		void OnUpdate(TimeStep TS);

		Entity() = default;

		Entity(Scene* Parent, JSON EntityJSON);

		~Entity();

	private:

		Scene* _Parent;

		std::string _Name;

		bool _ErrorOccured = false;

		std::unordered_map<uint64_t, SimpleComponent*> _Components;

		static std::unordered_map<std::string, uint64_t> _ComponentTypeIDs;
	};			
	
	template<typename T>
	bool Entity::RemoveComponent()
	{
		if (!this->HasComponent<T>())
		{
			VOLUND_CORE_WARNING("Cant remove a component from a entity without that component.");
			return false;
		}

		uint64_t Hash = typeid(T).hash_code();
		delete this->_Components[Hash];
		this->_Components.erase(Hash);

		return true;
	}

	template<typename T>
	T* Entity::GetComponent()
	{
		if (!this->HasComponent<T>())
		{
			VOLUND_CORE_WARNING("Cant get a component from a entity without that component.");
			return nullptr;
		}

		uint64_t Hash = typeid(T).hash_code();
		return this->_Components[Hash];
	}

	template<typename T>
	bool Entity::HasComponent() const
	{
		uint64_t Hash = typeid(T).hash_code();
		return this->_Components.find(Hash) != this->_Components.end();
	}
}

