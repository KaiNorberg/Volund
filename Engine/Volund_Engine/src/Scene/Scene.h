#pragma once

#include "Entity/Entity.h"

namespace Volund
{
	class Scene
	{
	public:

		bool Error();

		Scene(std::filesystem::path FilePath);

	private:

		std::string Name;

		bool ErrorOccured = false;
	
		std::vector<Entity> Entities;
	};
}

