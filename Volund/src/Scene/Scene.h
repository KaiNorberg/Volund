#pragma once

#include "Entity/Entity.h"

namespace Volund
{
	class Scene
	{
	public:

		 Entity* CreateEntity(std::string const& Name);

		 bool DeleteEntity(std::string const& Name);

		 Entity* GetEntity(std::string const& Name);

		 bool HasEntity(std::string const& Name) const;

		 virtual void OnUpdate(TimeStep TS) = 0;

		 void Update(TimeStep TS);

		 Scene() = default;

		 ~Scene();

	private:
	
		std::vector<Entity*> _Entities;
	};
}

