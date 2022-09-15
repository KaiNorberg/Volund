#pragma once

#include "Component/Component.h"

#include "VML/VML.h"

#include "Container/Container.h"

namespace Volund
{
	class Scene;

	class Entity
	{
	public:
		std::string GetName();

		Scene* GetScene() const;

		template <typename T, class... ARGS>
		Ref<T> CreateComponent(ARGS&&... Args);

		template <typename T>
		void DeleteComponent(uint32_t Index = 0);

		template <typename T>
		Ref<T> GetComponent(uint32_t Index = 0);

		template <typename T>
		bool HasComponent(uint32_t Index = 0);

		template <typename T>
		uint32_t ComponentAmount();

		template <typename T>
		const std::vector<Ref<Component>>& ComponentView();

		void OnEvent(Event* E) const;

		void OnUpdate(TimeStep TS) const;

		VML Serialize() const;

		Entity() = default;

		Entity(Scene* Parent, std::string_view Name = "");

		~Entity();

	private:

		Scene* _Parent;

		std::string _Name;

		Container<Component> _ComponentContainer;
	};

	template <typename T, class... ARGS>
	Ref<T> Entity::CreateComponent(ARGS&&... Args)
	{
		Ref<T> NewComponent = std::make_shared<T>(Args...);
		NewComponent->SetParent(this);
		NewComponent->OnCreate();

		this->_ComponentContainer.PushBack(NewComponent);
	
		return NewComponent;
	}

	template <typename T>
	void Entity::DeleteComponent(uint32_t Index)
	{
		this->_ComponentContainer.Get<T>()->OnDelete();
		this->_ComponentContainer.Erase<T>(Index);
	}

	template <typename T>
	Ref<T> Entity::GetComponent(uint32_t Index)
	{
		return this->_ComponentContainer.Get<T>(Index);
	}

	template <typename T>
	bool Entity::HasComponent(uint32_t Index)
	{
		return this->_ComponentContainer.Contains<T>(Index);
	}

	template <typename T>
	uint32_t Entity::ComponentAmount()
	{
		return this->_ComponentContainer.Size<T>();
	}

	template <typename T>
	const std::vector<Ref<Component>>& Entity::ComponentView()
	{
		return this->_ComponentContainer.View<T>();
	}
}
