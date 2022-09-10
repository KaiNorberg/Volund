#include "PCH/PCH.h"

#include "Scene.h"
#include "AssetLibrary/Asset/Assets.h"

#include "EventDispatcher/Event.h"
#include "Scene/Entity/Component/Components.h"

#include "VML/VML.h"

namespace Volund
{
	Ref<Entity> Scene::CreateEntity(const std::string& Name)
	{
		Ref<Entity> NewEntity = std::make_shared<Entity>(this, Name);

		if (this->HasEntity(NewEntity->GetName()))
		{
			VOLUND_WARNING("Duplicate entity detected");
			return nullptr;
		}

		this->_Entities.push_back(NewEntity);

		return NewEntity;
	}

	Ref<Entity> Scene::CreateEntity(const std::string& Name, const Vec3& Position, const Vec3& Rotation,
	                                const Vec3& Scale)
	{
		Ref<Entity> NewEntity = this->CreateEntity(Name);

		NewEntity->CreateComponent<Transform>(Position, Rotation, Scale);

		return NewEntity;
	}

	bool Scene::DeleteEntity(const std::string& Name)
	{
		for (uint64_t i = 0; i < this->_Entities.size(); i++)
		{
			if (this->_Entities[i]->GetName() == Name)
			{
				this->_Entities.erase(this->_Entities.begin() + (int64_t)i);
				return true;
			}
		}

		VOLUND_ERROR("Entity not found (%s)", Name.c_str());
		return false;
	}

	Ref<Entity> Scene::GetEntity(const std::string& Name)
	{
		for (uint64_t i = 0; i < this->_Entities.size(); i++)
		{
			if (this->_Entities[i]->GetName() == Name)
			{
				return this->_Entities[i];
			}
		}

		VOLUND_ERROR("Entity not found (%s)", Name.c_str());
		return nullptr;
	}

	bool Scene::HasEntity(const std::string& Name) const
	{
		for (uint64_t i = 0; i < this->_Entities.size(); i++)
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
		this->OnUpdate(TS);
		for (const auto& Entity : this->_Entities)
		{
			Entity->OnUpdate(TS);
		}
	}

	void Scene::EventCallback(Event* E)
	{
		this->OnEvent(E);
		for (const auto& Entity : this->_Entities)
		{
			Entity->OnEvent(E);
		}
	}

	void Scene::OnEvent(Event*)
	{
	}

	void Scene::OnUpdate(TimeStep)
	{
	}

	Ref<Scene> Scene::Deserialize(const std::string& FilePath)
	{
		VML SceneVML(FilePath);

		Ref<Scene> NewScene = std::make_shared<Scene>();

		NewScene->Assets.Deserialize<MeshAsset>(SceneVML.Get("Meshes"));

		NewScene->Assets.Deserialize<ShaderAsset>(SceneVML.Get("Shaders"));

		NewScene->Assets.Deserialize<TextureAsset>(SceneVML.Get("Textures"));

		NewScene->Assets.Deserialize<MaterialAsset>(SceneVML.Get("Materials"));

		VML& EntitiesVML = SceneVML["Entities"];
		for (auto& [EntityName, EntityVML] : EntitiesVML)
		{
			VOLUND_INFO("%s", EntityName.c_str());

			Ref<Entity> NewEntity = NewScene->CreateEntity(EntityName);

			for (auto& [ComponentName, ComponentVML] : EntityVML)
			{
				const std::string& ComponentType = (ComponentVML.Get("Type")).String();

				if (ComponentType == "Camera")
				{
					Ref<Camera> NewCamera = NewEntity->CreateComponent<Camera>();

					if (ComponentVML.Get("IsActive"))
					{
						NewEntity->CreateComponent<Camera>()->SetActive();
					}

					NewCamera->FOV = ComponentVML.Get("FOV");
					NewCamera->NearPlane = ComponentVML.Get("NearPlane");
					NewCamera->FarPlane = ComponentVML.Get("FarPlane");
				}
				else if (ComponentType == "CameraMovement")
				{
					NewEntity->CreateComponent<CameraMovement>(ComponentVML.Get("Speed"), ComponentVML.Get("Sensitivity"));
				}
				else if (ComponentType == "MeshRenderer")
				{
					Ref<MeshAsset> ObjectMesh = NewScene->Assets.GetAsset<MeshAsset>(
						ComponentVML.Get("Mesh").GetAs<std::string>());
					Ref<MaterialAsset> ObjectMaterial = NewScene->Assets.GetAsset<MaterialAsset>(
						ComponentVML.Get("Material").GetAs<std::string>());

					NewEntity->CreateComponent<MeshRenderer>(ObjectMesh, ObjectMaterial);
				}
				else if (ComponentType == "PointLight")
				{
					VMLEntry ColorVML = ComponentVML.Get("Color");

					RGB Color = RGB(ColorVML[0], ColorVML[1], ColorVML[2]);

					NewEntity->CreateComponent<PointLight>(Color);
				}
				else if (ComponentType == "Transform")
				{
					VMLEntry PositionVML = ComponentVML.Get("Position");
					VMLEntry RotationVML = ComponentVML.Get("Rotation");
					VMLEntry ScaleVML = ComponentVML.Get("Scale");

					Vec3 Position = Vec3(PositionVML[0], PositionVML[1], PositionVML[2].GetAs<float>());
					Vec3 Rotation = Vec3(RotationVML[0], RotationVML[1], RotationVML[2].GetAs<float>());
					Vec3 Scale = Vec3(ScaleVML[0], ScaleVML[1], ScaleVML[2]);

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

	void Scene::Serialize(const std::string& FilePath)
	{
		VML SceneVML;

		SceneVML.PushBack("Meshes", this->Assets.Serialize<MeshAsset>());

		SceneVML.PushBack("Shaders", this->Assets.Serialize<ShaderAsset>());

		SceneVML.PushBack("Textures", this->Assets.Serialize<TextureAsset>());

		SceneVML.PushBack("Materials", this->Assets.Serialize<MaterialAsset>());

		VML EntitiesVML;
		for (uint64_t i = 0; i < this->_Entities.size(); i++)
		{
			EntitiesVML.PushBack(this->_Entities[i]->GetName(), this->_Entities[i]->Serialize());
		}
		SceneVML.PushBack("Entities", EntitiesVML);

		SceneVML.Write(FilePath);
	}

	Scene::Scene()
	{
		VOLUND_INFO("Initializing Scene...");
	}
}
