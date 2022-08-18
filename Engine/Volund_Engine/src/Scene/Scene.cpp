#include "PCH/PCH.h"

#include "Scene.h"

namespace Volund
{
	bool Scene::Error()
	{
		return ErrorOccured;
	}

	Scene::Scene(std::filesystem::path FilePath)
	{
		this->Name = FilePath.filename().string();

		std::ifstream EntitiesFile(FilePath.string() + "\\Entities.json");
		if (!EntitiesFile.is_open())
		{
			Console::LogError("No Entities.json file found for ", this->Name);
		}

		JSON EntitiesJSON = JSON::parse(EntitiesFile);

		for (JSON Entry : EntitiesJSON)
		{
			Entity NewEntity = Entity(Entry);

			if (!NewEntity.Error())
			{
				this->Entities.push_back(NewEntity);
			}
		}
	}
}