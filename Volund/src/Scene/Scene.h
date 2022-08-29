#pragma once

#include "Entity/Entity.h"

namespace Volund
{
	class Event;

	class Scene
	{
	public:

		 Entity* CreateEntity(std::string const& Name);

		 bool DeleteEntity(std::string const& Name);

		 Entity* GetEntity(std::string const& Name);

		 bool HasEntity(std::string const& Name) const;

		 void Update(TimeStep TS);

		 void EventCallback(Event* E);

		 virtual void OnEvent(Event* E) {};

		 virtual void OnUpdate(TimeStep TS) {};

		 Scene() = default;

		 ~Scene();

	private:
	
		std::vector<Entity*> _Entities;
	};
}

