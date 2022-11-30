#include "PCH/PCH.h"

#include "Scene.h"

#include "Scene/Component/Components.h"

#include "VML/VML.h"
#include "Lua/Lua.h"

#include "Filesystem/Filesystem.h"

#include "Renderer/Renderer.h"

extern "C"
{
#include "lua/include/lua.h"
#include "lua/include/lauxlib.h"
#include "lua/include/lualib.h"
}

namespace Volund
{
	static Scene* LuaActiveScene = nullptr;

	int LuaCreateEntity(lua_State* L)
	{
		Entity NewEntity = LuaActiveScene->CreateEntity();

		lua_pushnumber(L, NewEntity);

		return 1;
	}

	int LuaAddComponent(lua_State* L)
	{
		LuaValue Table = LuaValue(-1, L);

		int EntityID = Table.Number(1);

		if (!LuaActiveScene->HasEntity(EntityID))
		{
			VOLUND_WARNING("Invalid EntityID %d!", EntityID);

			return 0;
		}

		std::string Component = Table.String(2);

		VOLUND_INFO("%s %d", Component.c_str(), EntityID);

		if (Component == "Camera")
		{
			auto NewComponent = LuaActiveScene->CreateComponent<Camera>(EntityID);

			int IsActive = Table.Int("IsActive");
			if (IsActive)
			{
				NewComponent->SetActive();
			}

			float FOV = Table.Number("FOV");
			if (FOV != NULL_LUA)
			{
				NewComponent->FOV = FOV;
			}

			float NearPlane = Table.Number("NearPlane");
			if (NearPlane != NULL_LUA)
			{
				NewComponent->NearPlane = NearPlane;
			}

			float FarPlane = Table.Number("FarPlane");
			if (FarPlane != NULL_LUA)
			{
				NewComponent->FarPlane = FarPlane;
			}
		}
		else if (Component == "CameraMovement")
		{
			auto NewComponent = LuaActiveScene->CreateComponent<CameraMovement>(EntityID);

			float Speed = Table.Number("Speed");
			if (Speed != NULL_LUA)
			{
				NewComponent->Speed = Speed;
			}

			float Sensitivity = Table.Number("Sensitivity");
			if (Speed != NULL_LUA)
			{
				NewComponent->Sensitivity = Sensitivity;
			}
		}
		else if (Component == "MeshRenderer")
		{
			Ref<Mesh> MeshAsset = Mesh::Create(Table.String("Mesh"));
			Ref<Material> MaterialAsset = Material::Create(Table.String("Material"));

			LuaActiveScene->CreateComponent<MeshRenderer>(EntityID, MeshAsset, MaterialAsset);
		}
		else if (Component == "PointLight")
		{
			auto NewComponent = LuaActiveScene->CreateComponent<PointLight>(EntityID);

			Vec3 Color = Table.Vector3("Color");
			if (Color.x != NULL_LUA)
			{
				NewComponent->Color = Color;
			}

			float Brightness = Table.Number("Brightness");
			if (Brightness != NULL_LUA)
			{
				NewComponent->Brightness = Brightness;
			}
		}
		else if (Component == "Transform")
		{
			auto NewComponent = LuaActiveScene->CreateComponent<Transform>(EntityID);

			Vec3 Position = Table.Vector3("Position");
			if (Position.x != NULL_LUA)
			{
				NewComponent->Position = Position;
			}
			Vec3 Rotation = Table.Vector3("Rotation");
			if (Rotation.x != NULL_LUA)
			{
				NewComponent->SetRotation(Rotation);
			}
			Vec3 Scale = Table.Vector3("Scale");
			if (Scale.x != NULL_LUA)
			{
				NewComponent->Scale = Scale;
			}
		}
		else if (Component == "Tag")
		{
			std::string String = Table.String("String");

			auto NewComponent = LuaActiveScene->CreateComponent<Tag>(EntityID, String);
		}
		else
		{
			VOLUND_ERROR("Unknown Component type (%s)!", Component.c_str());
		}

		return 0;
	}

	static LuaLibrary SceneCreationLib =
	{
		{"CreateEntity", LuaCreateEntity},
		{"AddComponent", LuaAddComponent}
	};

	std::string Scene::GetFilepath()
	{
		return this->_Filepath;
	}

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
		VL::Camera* ActiveCamera = VL::Camera::GetActiveCamera(this);

		if (ActiveCamera != nullptr)
		{
			IVec2 ViewSize = RenderingAPI::GetViewSize();

			Renderer::Begin(ActiveCamera->GetViewMatrix(), ActiveCamera->GetProjectionMatrix((float)ViewSize.x / (float)ViewSize.y));

		}
		else
		{
			Renderer::Begin(Mat4x4(1.0f), Mat4x4(1.0f));
		}

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

		Renderer::End();
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

	Scene::Scene(std::string_view Filepath)
	{
		VOLUND_INFO("Deserializing Scene...");

		this->_Filepath = Filepath;

		std::string ParentPath = std::filesystem::path(Filepath).parent_path().string();
		VL::Filesystem::AddRelativeFilepath(ParentPath);

		LuaActiveScene = this;

		LuaContext Lua;
		Lua.AddLibrary(SceneCreationLib);
		Lua.DoFile(this->_Filepath);

		LuaActiveScene = nullptr;

		/*VML SceneVML = VML(Filepath);

		for (auto& [EntityName, EntityVML] : SceneVML)
		{
			Entity NewEntity = this->CreateEntity();

			for (auto& [ComponentName, ComponentVML] : EntityVML)
			{
				std::string_view ComponentType = (ComponentVML.Get("Type")).String();

				if (ComponentType == "Camera")
				{
					auto NewComponent = this->CreateComponent<Camera>(NewEntity);

					if (ComponentVML.ContainsEntry("IsActive") && ComponentVML.Get("IsActive"))
					{
						NewComponent->SetActive();
					}
					if (ComponentVML.ContainsEntry("FOV"))
					{
						NewComponent->FOV = ComponentVML.Get("FOV");
					}
					if (ComponentVML.ContainsEntry("NearPlane"))
					{
						NewComponent->NearPlane = ComponentVML.Get("NearPlane");
					}
					if (ComponentVML.ContainsEntry("FarPlane"))
					{
						NewComponent->FarPlane = ComponentVML.Get("FarPlane");
					}
				}
				else if (ComponentType == "CameraMovement")
				{
					auto NewComponent = this->CreateComponent<CameraMovement>(NewEntity);

					if (ComponentVML.ContainsEntry("Speed"))
					{
						NewComponent->Speed = ComponentVML.Get("Speed");
					}
					if (ComponentVML.ContainsEntry("Sensitivity"))
					{
						NewComponent->Sensitivity = ComponentVML.Get("Sensitivity");
					}
				}
				else if (ComponentType == "MeshRenderer")
				{
					Ref<Mesh> MeshAsset = Mesh::Create(ComponentVML.Get("Mesh"));
					Ref<Material> MaterialAsset = Material::Create(ComponentVML.Get("Material").String());

					this->CreateComponent<MeshRenderer>(NewEntity, MeshAsset, MaterialAsset);
				}
				else if (ComponentType == "PointLight")
				{
					auto NewComponent = this->CreateComponent<PointLight>(NewEntity);

					if (ComponentVML.ContainsEntry("Color"))
					{
						VMLEntry ColorVML = ComponentVML.Get("Color");

						RGB Color = RGB(ColorVML[0], ColorVML[1], ColorVML[2]);

						NewComponent->Color = Color;
					}					
					if (ComponentVML.ContainsEntry("Brightness"))
					{
						NewComponent->Brightness = ComponentVML.Get("Brightness");
					}
				}
				else if (ComponentType == "Transform")
				{
					auto NewComponent = this->CreateComponent<Transform>(NewEntity);

					if (ComponentVML.ContainsEntry("Position"))
					{
						VMLEntry PositionVML = ComponentVML.Get("Position");
						Vec3 Position = Vec3(PositionVML[0], PositionVML[1], PositionVML[2]);

						NewComponent->Position = Position;
					}
					if (ComponentVML.ContainsEntry("Rotation"))
					{
						VMLEntry RotationVML = ComponentVML.Get("Rotation");
						Vec3 Rotation = Vec3(RotationVML[0], RotationVML[1], RotationVML[2]);

						NewComponent->SetRotation(Rotation);
					}
					if (ComponentVML.ContainsEntry("Scale"))
					{
						VMLEntry ScaleVML = ComponentVML.Get("Scale");
						Vec3 Scale = Vec3(ScaleVML[0], ScaleVML[1], ScaleVML[2]);

						NewComponent->Scale = Scale;
					}
				}
				else if (ComponentType == "Tag")
				{
					std::string String = ComponentVML.Get("String");

					this->CreateComponent<Tag>(NewEntity, String);
				}
				else
				{
					VOLUND_ERROR("Unknown Component type (%s)!", ComponentType.data());
				}
			}
		}*/

		VOLUND_INFO("Finished deserializing Scene!");
	}

	Scene::~Scene()
	{
		std::string ParentPath = std::filesystem::path(this->_Filepath).parent_path().string();
		VL::Filesystem::RemoveRelativeFilepath(ParentPath);
	}
}
