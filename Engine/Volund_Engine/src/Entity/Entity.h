#pragma once

#include "Component/SimpleComponent.h"

namespace Volund
{
	class Entity
	{
	public:

		bool Error();

		bool AddComponent(JSON ComponentJSON);

		bool RemoveComponent(std::string const& Name);

		SimpleComponent* GetComponent(std::string const& Name);

		bool HasComponent(std::string const& Name) const;

		Entity(JSON EntityJSON);

	private:

		bool ErrorOccured = false;

		std::unordered_map<std::string, SimpleComponent*> Components;
	};	
}

