#include "PCH/PCH.h"

#include "Scene.h"

#include "Scene/Component/Components.h"

#include "VML/VML.h"

namespace Volund
{
	Entity Scene::CreateEntity()
	{
		Entity NewEntity = this->_NewEntity;

		this->_Registry.push_back(std::pair<Entity, Container<Component>>(NewEntity, Container<Component>()));

		this->_NewEntity++;
		return NewEntity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		uint64_t Index = this->FindEntity(entity);

		if (Index != -1)
		{
			this->_Registry.erase(this->_Registry.begin() + Index);
		}
		else
		{
			VOLUND_ERROR("Unable to find entity (%d)", entity);
		}
	}

	bool Scene::HasEntity(Entity entity) const
	{
		return this->FindEntity(entity) != -1;
	}

	void Scene::DeleteComponent(Component* component)
	{
		for (auto& [entity, Container] : this->_Registry)
		{
			if (Container.Erase(component))
			{
				return;
			}
		}			
		
		VOLUND_ERROR("Unable to find component (%d)", component);
	}

	void Scene::OnUpdate(TimeStep TS)
	{
		for (const auto& [entity, Container] : this->_Registry)
		{
			for (const auto& View : Container)
			{
				for (const auto& component : View)
				{
					component->OnUpdate(TS);
				}
			}
		}
	}

	void Scene::OnEvent(Event* E)
	{
		for (const auto& [entity, Container] : this->_Registry)
		{
			for (const auto& View : Container)
			{
				for (const auto& component : View)
				{
					component->OnEvent(E);
				}
			}
		}
	}

	Ref<Scene> Scene::Copy(Ref<Scene> Other)
	{
		return Deserialize(Other->Serialize());
	}

	Ref<Scene> Scene::Deserialize(std::string_view Filepath)
	{
		return Deserialize(VML(Filepath));
	}

	Ref<Scene> Scene::Deserialize(VML SceneVML)
	{
		VOLUND_INFO("Deserializing Scene...");

		Ref<Scene> NewScene = std::make_shared<Scene>();

		for (auto& [EntityName, EntityVML] : SceneVML)
		{
			Entity NewEntity = NewScene->CreateEntity();

			for (auto& [ComponentName, ComponentVML] : EntityVML)
			{
				std::string_view ComponentType = (ComponentVML.Get("Type")).String();

				if (ComponentType == "Camera")
				{
					Ref<Camera> NewCamera = NewScene->CreateComponent<Camera>(NewEntity);

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
					NewScene->CreateComponent<CameraMovement>(NewEntity, ComponentVML.Get("Speed"), ComponentVML.Get("Sensitivity"));
				}
				else if (ComponentType == "MeshRenderer")
				{
					Ref<Mesh> MeshAsset = Mesh::Create(ComponentVML.Get("Mesh"));
					Ref<Material> MaterialAsset = Material::Create(ComponentVML.Get("Material").String());

					NewScene->CreateComponent<MeshRenderer>(NewEntity, MeshAsset, MaterialAsset);
				}
				else if (ComponentType == "PointLight")
				{
					VMLEntry ColorVML = ComponentVML.Get("Color");
					VMLEntry BrightnessVML = ComponentVML.Get("Brightness");

					RGB Color = RGB(ColorVML[0], ColorVML[1], ColorVML[2]);

					NewScene->CreateComponent<PointLight>(NewEntity, Color, BrightnessVML);
				}
				else if (ComponentType == "Transform")
				{
					VMLEntry PositionVML = ComponentVML.Get("Position");
					VMLEntry RotationVML = ComponentVML.Get("Rotation");
					VMLEntry ScaleVML = ComponentVML.Get("Scale");

					Vec3 Position = Vec3(PositionVML[0], PositionVML[1], PositionVML[2].GetAs<float>());
					Vec3 Rotation = Vec3(RotationVML[0], RotationVML[1], RotationVML[2].GetAs<float>());
					Vec3 Scale = Vec3(ScaleVML[0], ScaleVML[1], ScaleVML[2]);

					NewScene->CreateComponent<Transform>(NewEntity, Position, Rotation, Scale);
				}
				else if (ComponentType == "Tag")
				{
					std::string String = ComponentVML.Get("String");

					NewScene->CreateComponent<Tag>(NewEntity, String);
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

	void Scene::Serialize(std::string_view Filepath)
	{
		VML SceneVML = this->Serialize();
		SceneVML.Write(Filepath);
	}

	VML Scene::Serialize()
	{
		VOLUND_INFO("Serializing Scene...");

		VML SceneVML;

		for (const auto& [entity, Container] : this->_Registry)
		{
			VML EntityVML;
			uint32_t i = 0;
			for (const auto& ComponentView : Container)
			{
				for (const auto& Component : ComponentView)
				{
					EntityVML.PushBack("Component" + std::to_string(i), Component->Serialize());
					i++;
				}
			}
			SceneVML.PushBack("Entity" + std::to_string(entity), EntityVML);
		}

		VOLUND_INFO("Finished serializing Scene!");

		return SceneVML;
	}

	Registry::iterator Scene::begin()
	{
		return this->_Registry.begin();
	}

	Registry::iterator Scene::end()
	{
		return this->_Registry.end();
	}

	Registry::const_iterator Scene::begin() const
	{
		return this->_Registry.begin();
	}

	Registry::const_iterator Scene::end() const
	{
		return this->_Registry.end();
	}

	uint64_t Scene::FindEntity(Entity entity) const
	{
		for (int i = 0; i < this->_Registry.size(); i++)
		{
			if (_Registry[i].first == entity)
			{
				return i;
			}
		}

		return -1;
	}

	Scene::Scene()
	{
		VOLUND_INFO("Initializing Scene...");
	}
}
