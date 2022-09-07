#include "PCH/PCH.h"

#include "Scene.h"

#include "EventDispatcher/Event.h"
#include "Component/Components.h"

namespace Volund
{
	Ref<Entity> Scene::CreateEntity(std::string const& Name)
	{
		Ref<Entity> NewEntity = Ref<Entity>(new Entity(this, Name));

		if (this->HasEntity(NewEntity->GetName()))
		{
			VOLUND_WARNING("Duplicate entity detected");
			return nullptr;
		}

		this->_Entities.push_back(NewEntity);

		return NewEntity;
	}

	Ref<Entity> Scene::CreateEntity(std::string const& Name, Vec3 const& Position, Vec3 const& Rotation, Vec3 const& Scale)
	{
		Ref<Entity> NewEntity = this->CreateEntity(Name);

		NewEntity->CreateComponent<Transform>(Position, Rotation, Scale);

		return NewEntity;
	}

	bool Scene::DeleteEntity(std::string const& Name)
	{
		for (int i = 0; i < this->_Entities.size(); i++)
		{
			if (this->_Entities[i]->GetName() == Name)
			{
				this->_Entities.erase(this->_Entities.begin() + i);		
				return true;
			}
		}

		VOLUND_ERROR("Entity not found (%s)", Name.c_str());
		return false;
	}

	Ref<Entity> Scene::GetEntity(std::string const& Name)
	{
		for (int i = 0; i < this->_Entities.size(); i++)
		{
			if (this->_Entities[i]->GetName() == Name)
			{
				return this->_Entities[i];
			}
		}

		VOLUND_ERROR("Entity not found (%s)", Name.c_str());
		return nullptr;
	}

	bool Scene::HasEntity(std::string const& Name) const
	{
		for (int i = 0; i < this->_Entities.size(); i++)
		{
			if (this->_Entities[i]->GetName() == Name)
			{
				return true;
			}
		}

		return false;
	}

	void Scene::Update(TimeStep TS)
	{
		for (auto const& Entity : this->_Entities)
		{
			Entity->OnUpdate(TS);
		}
	}

	void Scene::EventCallback(Event* E)
	{
		for (auto const& Entity : this->_Entities)
		{
			Entity->OnEvent(E);
		}
	}

	Ref<Scene> Scene::Deserialize(std::string const& FilePath)
	{
		VOLUND_INFO("Deserializing Scene (%s)...", FilePath.c_str());

		JSON SceneJSON = JSON::Load(FilePath);

		Ref<Scene> NewScene = Ref<Scene>(new Scene());

		NewScene->Assets.Deserialize<MeshAsset>(SceneJSON["Meshes"]);

		NewScene->Assets.Deserialize<ShaderAsset>(SceneJSON["Shaders"]);

		NewScene->Assets.Deserialize<TextureAsset>(SceneJSON["Textures"]);

		NewScene->Assets.Deserialize<MaterialAsset>(SceneJSON["Materials"]);

		JSON EntitiesJSON = SceneJSON["Entities"];
		for (int i = 0; i < EntitiesJSON.Size(); i++)
		{
			Ref<Entity> NewEntity = NewScene->CreateEntity(EntitiesJSON[i]["Name"]);

			JSON ComponentsJSON = EntitiesJSON[i]["Components"];

			for (int j = 0; j < ComponentsJSON.Size(); j++)
			{
				JSON ComponentJSON = ComponentsJSON[j];
				std::string ComponentType = ComponentJSON["Type"];

				if (ComponentType == "Camera")
				{
					Ref<Camera> NewCamera = NewEntity->CreateComponent<Camera>();

					if (ComponentJSON["IsActive"])
					{
						NewEntity->CreateComponent<Camera>()->SetActive();
					}

					NewCamera->FOV = ComponentJSON["FOV"];
					NewCamera->NearPlane = ComponentJSON["NearPlane"];
					NewCamera->FarPlane = ComponentJSON["FarPlane"];
				}
				else if (ComponentType == "CameraMovement")
				{
					NewEntity->CreateComponent<CameraMovement>(ComponentJSON["Speed"], ComponentJSON["Sensitivity"]);
				}
				else if (ComponentType == "MeshRenderer")
				{
					Ref<MeshAsset> ObjectMesh = NewScene->Assets.GetAsset<MeshAsset>(ComponentJSON["Mesh"].GetAs<std::string>());
					Ref<MaterialAsset> ObjectMaterial = NewScene->Assets.GetAsset<MaterialAsset>(ComponentJSON["Material"].GetAs<std::string>());

					NewEntity->CreateComponent<MeshRenderer>(ObjectMesh, ObjectMaterial);
				}
				else if (ComponentType == "PointLight")
				{
					RGB Color = Vec3(ComponentJSON["Color"][0], ComponentJSON["Color"][1], ComponentJSON["Color"][2]);

					NewEntity->CreateComponent<PointLight>(Color);
				}
				else if (ComponentType == "Transform")
				{
					Vec3 Position = Vec3(ComponentJSON["Position"][0], ComponentJSON["Position"][1], ComponentJSON["Position"][2]);
					Vec3 Rotation = Vec3(ComponentJSON["Rotation"][0], ComponentJSON["Rotation"][1], ComponentJSON["Rotation"][2]);
					Vec3 Scale = Vec3(ComponentJSON["Scale"][0], ComponentJSON["Scale"][1], ComponentJSON["Scale"][2]);

					NewEntity->CreateComponent<Transform>(Position, Rotation, Scale);
				}
				else
				{
					VOLUND_ERROR("Unknown Component type (%s)!", ComponentType.c_str());
				}
			}

		}

		VOLUND_INFO("Finished deserializing Scene!");

		return NewScene;
	}

	void Scene::Serialize(std::string const& FilePath)
	{
		JSON SceneJSON;

		SceneJSON.AddEntry("Meshes", this->Assets.Serialize<MeshAsset>());

		SceneJSON.AddEntry("Shaders", this->Assets.Serialize<ShaderAsset>());

		SceneJSON.AddEntry("Textures", this->Assets.Serialize<TextureAsset>());

		SceneJSON.AddEntry("Materials", this->Assets.Serialize<MaterialAsset>());

		JSON EntitiesJSON = {};
		for (int i = 0; i < this->_Entities.size(); i++)
		{
			EntitiesJSON.PushBack(this->_Entities[i]->Serialize());
		}
		SceneJSON.AddEntry("Entities", EntitiesJSON);

		SceneJSON.Save(FilePath);
	}

	Scene::Scene()
	{
		VOLUND_INFO("Initializing Scene...");
	}
}