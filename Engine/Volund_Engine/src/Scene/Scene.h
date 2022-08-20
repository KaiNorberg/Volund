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

		void Update();

		Scene() = default;

		Scene(std::filesystem::path FilePath);

		~Scene();

	private:

		std::string Name;

		bool ErrorOccured = false;
	
		std::unordered_map<std::string, Entity*> Entities;
	};
}

