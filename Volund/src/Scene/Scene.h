#pragma once

#include "Entity/Entity.h"

namespace Volund
{
	class Scene
	{
	public:

		 bool Error();

		 Entity* AddEntity(JSON EntityJSON);

		 bool RemoveEntity(std::string const& Name);

		 Entity* GetEntity(std::string const& Name);

		 bool HasEntity(std::string const& Name) const;

		 void OnUpdate();

		 Scene() = default;

		 Scene(std::filesystem::path FilePath);

		 ~Scene();

	private:

		std::string _Name;

		bool _ErrorOccured = false;
	
		std::vector<Entity*> _Entities;
	};
}

