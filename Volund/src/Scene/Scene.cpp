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
	int Scene::LuaCreateEntity(lua_State* L)
	{
		Entity NewEntity = VL::Scene::CreateEntity();

		lua_pushnumber(L, (lua_Number)NewEntity);

		return 1;
	}

	int Scene::LuaAddComponent(lua_State* L)
	{
		LuaValue Table = LuaValue(-1, L);

		Entity EntityID = Table.Number(1);

		if (!VL::Scene::HasEntity(EntityID))
		{
			VOLUND_WARNING("Invalid EntityID %d!", EntityID);

			return 0;
		}

		std::string Component = Table.String(2);

		if (Component == "Camera")
		{
			auto NewComponent = VL::Scene::CreateComponent<Camera>(EntityID);

			uint64_t IsActive = Table.Int("IsActive");
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
			auto NewComponent = VL::Scene::CreateComponent<CameraMovement>(EntityID);

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

			VL::Scene::CreateComponent<MeshRenderer>(EntityID, MeshAsset, MaterialAsset);
		}
		else if (Component == "PointLight")
		{
			auto NewComponent = VL::Scene::CreateComponent<PointLight>(EntityID);

			Vec3 Color = Table.Vector<3>("Color");
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
			auto NewComponent = VL::Scene::CreateComponent<Transform>(EntityID);

			Vec3 Position = Table.Vector<3>("Position");
			if (Position.x != NULL_LUA)
			{
				NewComponent->Position = Position;
			}
			Vec3 Rotation = Table.Vector<3>("Rotation");
			if (Rotation.x != NULL_LUA)
			{
				NewComponent->SetRotation(Rotation);
			}
			Vec3 Scale = Table.Vector<3>("Scale");
			if (Scale.x != NULL_LUA)
			{
				NewComponent->Scale = Scale;
			}
		}
		else if (Component == "Tag")
		{
			std::string String = Table.String("String");

			auto NewComponent = VL::Scene::CreateComponent<Tag>(EntityID, String);
		}
		else
		{
			VOLUND_ERROR("Unknown Component type (%s)!", Component.c_str());
		}

		return 0;
	}

	std::string Scene::GetFilepath()
	{
		return _Data.Filepath;
	}

	Entity Scene::CreateEntity()
	{
		Entity NewEntity = _Data.NewEntity;

		_Data.Registry.push_back(std::pair<Entity, Container<Component>>(NewEntity, Container<Component>()));

		_Data.NewEntity++;
		return NewEntity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		uint64_t Index = FindEntity(entity);

		if (Index != -1)
		{
			_Data.Registry.erase(_Data.Registry.begin() + Index);
		}
		else
		{
			VOLUND_ERROR("Unable to find entity (%d)", entity);
		}
	}

	bool Scene::HasEntity(Entity entity)
	{
		return FindEntity(entity) != -1;
	}

	void Scene::DeleteComponent(Component* component)
	{
		for (auto& [entity, Container] : _Data.Registry)
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
		VL::Camera* ActiveCamera = VL::Camera::GetActiveCamera();

		if (ActiveCamera != nullptr)
		{
			IVec2 ViewSize = RenderingAPI::GetViewSize();

			Renderer::Begin(ActiveCamera->GetViewMatrix(), ActiveCamera->GetProjectionMatrix((float)ViewSize.x / (float)ViewSize.y));

		}
		else
		{
			Renderer::Begin(Mat4x4(1.0f), Mat4x4(1.0f));
		}

		for (const auto& [entity, Container] : _Data.Registry)
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
		for (const auto& [entity, Container] : _Data.Registry)
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

	Registry::iterator Scene::begin()
	{
		return _Data.Registry.begin();
	}

	Registry::iterator Scene::end()
	{
		return _Data.Registry.end();
	}

	void Scene::Load(const std::string& Filepath)
	{
		if (!_Data.Filepath.empty())
		{
			std::string ParentPath = std::filesystem::path(_Data.Filepath).parent_path().string();
			VL::Filesystem::RemoveRelativeFilepath(ParentPath);
		}

		VOLUND_INFO("Deserializing Scene...");
		
		_Data = SceneData();
		_Data.Filepath = Filepath;

		std::string ParentPath = std::filesystem::path(Filepath).parent_path().string();
		VL::Filesystem::AddRelativeFilepath(ParentPath);

		LuaContext Lua;
		Lua.AddLibrary(_LuaLib);
		Lua.DoFile(_Data.Filepath);

		VOLUND_INFO("Finished deserializing Scene!");
	}

	uint64_t Scene::FindEntity(Entity entity)
	{
		for (int i = 0; i < _Data.Registry.size(); i++)
		{
			if (_Data.Registry[i].first == entity)
			{
				return i;
			}
		}

		return -1;
	}
}
