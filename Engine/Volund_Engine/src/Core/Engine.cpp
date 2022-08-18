#include "PCH/PCH.h"

#include "Engine.h"

namespace Volund
{
	Engine::Engine()
	{

	}

	void Engine::LoadScenes(std::string const& FilePath)
	{
		Console::Log("Loading scenes (", FilePath, ")...");

		for (auto& Directory : std::filesystem::recursive_directory_iterator(FilePath))
		{
			if (!Directory.is_directory())
			{
				continue;
			}

			Scene NewScene = Scene(Directory.path());

			if (!NewScene.Error())
			{
				this->Scenes.push_back(NewScene);
			}
		}
	}
}