#pragma once

#include "Scene/Scene.h"

namespace Volund
{
	class Engine
	{
	public:

		void LoadScenes(std::string const& FilePath);

		Engine();
			
	private:

		std::vector<Scene> Scenes;
	};
}
