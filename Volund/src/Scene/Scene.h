#pragma once

#include "Entity/Entity.h"

namespace Volund
{
	class Scene
	{
	public:

		VOLUND_API bool Error();

		VOLUND_API Entity* AddEntity(JSON EntityJSON);

		VOLUND_API bool RemoveEntity(std::string const& Name);

		VOLUND_API Entity* GetEntity(std::string const& Name);

		VOLUND_API bool HasEntity(std::string const& Name) const;

		VOLUND_API void OnUpdate();

		VOLUND_API Scene() = default;

		VOLUND_API Scene(std::filesystem::path FilePath);

		VOLUND_API ~Scene();

	private:

		std::string _Name;

		bool _ErrorOccured = false;
	
		std::vector<Entity*> _Entities;
	};
}

