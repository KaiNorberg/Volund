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

		JSON EntitiesJSON = JSON::Load(FilePath.string() + "\\Entities.json");

		for (JSON Entry : EntitiesJSON)
		{
			Entity NewEntity = Entity(Entry);

			if (!NewEntity.Error())
			{
				this->Entities.push_back(NewEntity);
			}
		}

		for (int i = 0; i < Entities.size(); i++)
		{
			if (Entities[i].HasComponent("Transform2D"))
			{
				Console::Log(((Transform2D*)(Entities[i].GetComponent("Transform2D")))->Position);
			}
		}
	}
}