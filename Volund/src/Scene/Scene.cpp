#include "PCH/PCH.h"

#include "Scene.h"

#include "EventDispatcher/Event.h"
#include "Scene/Entity/Component/Components.h"

#include "VML/VML.h"

namespace Volund
{
	Ref<Entity> Scene::CreateEntity(std::string_view Name)
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

	Ref<Entity> Scene::CreateEntity(std::string_view Name, const Vec3& Position, const Vec3& Rotation,
	                                const Vec3& Scale)
	{
		Ref<Entity> NewEntity = this->CreateEntity(Name);

		NewEntity->CreateComponent<Transform>(Position, Rotation, Scale);

		return NewEntity;
	}

	bool Scene::DeleteEntity(std::string_view Name)
	{
		for (uint64_t i = 0; i < this->_Entities.size(); i++)
		{
			if (this->_Entities[i]->GetName() == Name)
			{
				this->_Entities.erase(this->_Entities.begin() + (int64_t)i);
				return true;
			}
		}

		VOLUND_ERROR("Entity not found (%s)", Name.data());
		return false;
	}

	Ref<Entity> Scene::GetEntity(std::string_view Name)
	{
		for (uint64_t i = 0; i < this->_Entities.size(); i++)
		{
			if (this->_Entities[i]->GetName() == Name)
			{
				return this->_Entities[i];
			}
		}

		VOLUND_ERROR("Entity not found (%s)", Name.data());
		return nullptr;
	}

	bool Scene::HasEntity(std::string_view Name) const
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

	void Scene::OnUpdate(TimeStep TS)
	{
		for (const auto& Entity : this->_Entities)
		{
			Entity->OnUpdate(TS);
		}
	}

	void Scene::OnEvent(Event* E)
	{
		for (const auto& Entity : this->_Entities)
		{
			Entity->OnEvent(E);
		}
	}

	Ref<Scene> Scene::Deserialize(std::string_view FilePath)
	{
		VML SceneVML(FilePath);

		Ref<Scene> NewScene = std::make_shared<Scene>();

		for (auto& [EntityName, EntityVML] : SceneVML)
		{
			Ref<Entity> NewEntity = NewScene->CreateEntity(EntityName);

			for (auto& [ComponentName, ComponentVML] : EntityVML)
			{
				std::string_view ComponentType = (ComponentVML.Get("Type")).String();

				if (ComponentType == "Camera")
				{
					Ref<Camera> NewCamera = NewEntity->CreateComponent<Camera>();

					if (ComponentVML.Get("IsActive"))
					{
						NewCamera->SetActive();
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
					NewEntity->CreateComponent<MeshRenderer>(ComponentVML.Get("Mesh"), ComponentVML.Get("Material"));
				}
				else if (ComponentType == "PointLight")
				{
					VMLEntry ColorVML = ComponentVML.Get("Color");
					VMLEntry BrightnessVML = ComponentVML.Get("Brightness");

					RGB Color = RGB(ColorVML[0], ColorVML[1], ColorVML[2]);

					NewEntity->CreateComponent<PointLight>(Color, BrightnessVML);
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
					VOLUND_ERROR("Unknown Component type (%s)!", ComponentType.data());
				}
			}
		}

		VOLUND_INFO("Finished deserializing Scene!");

		return NewScene;
	}

	void Scene::Serialize(std::string_view FilePath)
	{
		VML SceneVML;

		VML EntitiesVML;
		for (uint64_t i = 0; i < this->_Entities.size(); i++)
		{
			EntitiesVML.PushBack(this->_Entities[i]->GetName(), this->_Entities[i]->Serialize());
		}
		SceneVML.PushBack("Entities", EntitiesVML);

		SceneVML.Write(FilePath);
	}

	std::vector<Ref<Entity>>::iterator Scene::begin()
	{
		return this->_Entities.begin();
	}

	std::vector<Ref<Entity>>::iterator Scene::end()
	{
		return this->_Entities.end();
	}

	std::vector<Ref<Entity>>::const_iterator Scene::begin() const
	{
		return this->_Entities.begin();
	}

	std::vector<Ref<Entity>>::const_iterator Scene::end() const
	{
		return this->_Entities.end();
	}

	Scene::Scene()
	{
		VOLUND_INFO("Initializing Scene...");
	}
}
