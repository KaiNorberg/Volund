#include "PCH/PCH.h"
#include "LuaEntity.h"

#include "Scene/Component/Components.h"

#include "Lua/LuaComponent/LuaComponent.h"
#include "Lua/LuaMaterial/LuaMaterial.h"
#include "Lua/LuaMesh/LuaMesh.h"

namespace Volund
{
	void LuaEntity::AddComponent(sol::this_state S, LuaComponentID Component, const sol::table& Table)
	{
		if (!this->_Scene->HasEntity(this->_Entity))
		{
			VOLUND_WARNING("Invalid this->_Entity %d!", this->_Entity);

			return;
		}

		switch (Component)
		{
		case LuaComponentID::CAMERA:
		{
			auto NewComponent = this->_Scene->CreateComponent<Camera>(this->_Entity);

			if (Table["FOV"] != sol::lua_nil)
			{
				NewComponent->FOV = Table["FOV"];
			}

			if (Table["NearPlane"] != sol::lua_nil)
			{
				NewComponent->NearPlane = Table["NearPlane"];
			}

			if (Table["FarPlane"] != sol::lua_nil)
			{
				NewComponent->FarPlane = Table["FarPlane"];
			}
		}
		break;
		case LuaComponentID::CAMERA_MOVEMENT:
		{
			auto NewComponent = this->_Scene->CreateComponent<CameraMovement>(this->_Entity);

			if (Table["Speed"] != sol::lua_nil)
			{
				NewComponent->Speed = Table["Speed"];
			}

			if (Table["Sensitivity"] != sol::lua_nil)
			{
				NewComponent->Sensitivity = Table["Sensitivity"];
			}
		}
		break;
		case LuaComponentID::MESH_RENDERER:
		{
			if (Table["Mesh"] != sol::lua_nil && Table["Material"] != sol::lua_nil)
			{
				LuaMesh MeshAsset = Table["Mesh"];
				LuaMaterial MaterialAsset = Table["Material"];

				this->_Scene->CreateComponent<MeshRenderer>(this->_Entity, MeshAsset.Get(), MaterialAsset.Get());
			}
			else
			{
				VOLUND_WARNING("Unable to read mesh or material from MeshRenderer table!");
			}
		}
		break;
		case LuaComponentID::POINT_LIGHT:
		{
			auto NewComponent = this->_Scene->CreateComponent<PointLight>(this->_Entity);

			if (Table["Color"] != sol::lua_nil)
			{
				Vec3 Color = Table["Color"];
				NewComponent->Color = Color;
			}

			if (Table["Brightness"] != sol::lua_nil)
			{
				NewComponent->Brightness = Table["Brightness"];
			}
		}
		break;
		case LuaComponentID::SCRIPT:
		{
			auto NewComponent = this->_Scene->CreateComponent<Script>(this->_Entity, S, Table["Script"], Table);
		}
		break;
		case LuaComponentID::TAG:
		{
			std::string String = Table["String"];

			auto NewComponent = this->_Scene->CreateComponent<Tag>(this->_Entity, String);
		}
		break;
		case LuaComponentID::TRANSFORM:
		{
			auto NewComponent = this->_Scene->CreateComponent<Transform>(this->_Entity);

			if (Table["Position"] != sol::lua_nil)
			{
				Vec3 Position = Table["Position"];
				NewComponent->Position = Position;
			}

			if (Table["Rotation"] != sol::lua_nil)
			{
				Vec3 Rotation = Table["Rotation"];
				NewComponent->SetRotation(Rotation);
			}

			if (Table["Scale"] != sol::lua_nil)
			{
				Vec3 Scale = Table["Scale"];
				NewComponent->Scale = Scale;
			}
		}
		break;
		default:
		{
			VOLUND_WARNING("Unknown Component type (%d)!", Component);
		}
		break;
		}
	}

	void LuaEntity::DeleteComponent(sol::this_state S, LuaComponentID Component, uint64_t I)
	{
		if (!this->_Scene->HasEntity(this->_Entity))
		{
			VOLUND_WARNING("Invalid this->_Entity %d!", this->_Entity);

			return;
		}

		switch (Component)
		{
		case LuaComponentID::CAMERA:
		{
			this->_Scene->DeleteComponent<Camera>(this->_Entity, I);
		}
		break;
		case LuaComponentID::CAMERA_MOVEMENT:
		{
			this->_Scene->DeleteComponent<CameraMovement>(this->_Entity, I);
		}
		break;
		case LuaComponentID::MESH_RENDERER:
		{
			this->_Scene->DeleteComponent<MeshRenderer>(this->_Entity, I);
		}
		break;
		case LuaComponentID::POINT_LIGHT:
		{
			this->_Scene->DeleteComponent<PointLight>(this->_Entity, I);
		}
		break;
		case LuaComponentID::SCRIPT:
		{
			this->_Scene->DeleteComponent<Script>(this->_Entity, I);
		}
		break;
		case LuaComponentID::TAG:
		{
			this->_Scene->DeleteComponent<Tag>(this->_Entity, I);
		}
		break;
		case LuaComponentID::TRANSFORM:
		{
			this->_Scene->DeleteComponent<Transform>(this->_Entity, I);
		}
		break;
		default:
		{
			VOLUND_ERROR("Unknown Component type (%d)!", Component);
		}
		break;
		}
	}

	bool LuaEntity::HasComponent(LuaComponentID Component)
	{
		if (!this->_Scene->HasEntity(this->_Entity))
		{
			VOLUND_WARNING("Invalid this->_Entity %d!", this->_Entity);

			return false;
		}

		switch (Component)
		{
		case LuaComponentID::CAMERA:
		{
			return this->_Scene->HasComponent<Camera>(this->_Entity);
		}
		break;
		case LuaComponentID::CAMERA_MOVEMENT:
		{
			return this->_Scene->HasComponent<CameraMovement>(this->_Entity);
		}
		break;
		case LuaComponentID::MESH_RENDERER:
		{
			return this->_Scene->HasComponent<MeshRenderer>(this->_Entity);
		}
		break;
		case LuaComponentID::POINT_LIGHT:
		{
			return this->_Scene->HasComponent<PointLight>(this->_Entity);
		}
		break;
		case LuaComponentID::SCRIPT:
		{
			return this->_Scene->HasComponent<Script>(this->_Entity);
		}
		break;
		case LuaComponentID::TAG:
		{
			return this->_Scene->HasComponent<Tag>(this->_Entity);
		}
		break;
		case LuaComponentID::TRANSFORM:
		{
			return this->_Scene->HasComponent<Transform>(this->_Entity);
		}
		break;
		default:
		{
			VOLUND_ERROR("Unknown Component type (%d)!", Component);
		}
		break;
		}

		return false;
	}

	uint64_t LuaEntity::ComponentAmount(LuaComponentID Component)
	{
		if (!this->_Scene->HasEntity(this->_Entity))
		{
			VOLUND_WARNING("Invalid this->_Entity %d!", this->_Entity);

			return 0;
		}

		switch (Component)
		{
		case LuaComponentID::CAMERA:
		{
			return this->_Scene->ComponentAmount<Camera>(this->_Entity);
		}
		break;
		case LuaComponentID::CAMERA_MOVEMENT:
		{
			return this->_Scene->ComponentAmount<CameraMovement>(this->_Entity);
		}
		break;
		case LuaComponentID::MESH_RENDERER:
		{
			return this->_Scene->ComponentAmount<MeshRenderer>(this->_Entity);
		}
		break;
		case LuaComponentID::POINT_LIGHT:
		{
			return this->_Scene->ComponentAmount<PointLight>(this->_Entity);
		}
		break;
		case LuaComponentID::SCRIPT:
		{
			return this->_Scene->ComponentAmount<Script>(this->_Entity);
		}
		break;
		case LuaComponentID::TAG:
		{
			return this->_Scene->ComponentAmount<Tag>(this->_Entity);
		}
		break;
		case LuaComponentID::TRANSFORM:
		{
			return this->_Scene->ComponentAmount<Transform>(this->_Entity);
		}
		break;
		default:
		{
			VOLUND_ERROR("Unknown Component type (%d)!", Component);
		}
		break;
		}

		return 0;
	}

	sol::table LuaEntity::GetComponent(sol::this_state S, LuaComponentID Component, uint64_t I)
	{
		if (!this->_Scene->HasEntity(this->_Entity))
		{
			VOLUND_WARNING("Invalid this->_Entity %d!", this->_Entity);

			return sol::make_object(S, VL::Component());
		}

		switch (Component)
		{
		case LuaComponentID::CAMERA:
		{
			return GenerateComponentTable(S, this->_Scene->GetComponent<Camera>(this->_Entity, I));
		}
		break;
		case LuaComponentID::CAMERA_MOVEMENT:
		{
			return GenerateComponentTable(S, this->_Scene->GetComponent<CameraMovement>(this->_Entity, I));
		}
		break;
		case LuaComponentID::MESH_RENDERER:
		{
			return GenerateComponentTable(S, this->_Scene->GetComponent<MeshRenderer>(this->_Entity, I));
		}
		break;
		case LuaComponentID::POINT_LIGHT:
		{
			return GenerateComponentTable(S, this->_Scene->GetComponent<PointLight>(this->_Entity, I));
		}
		break;
		case LuaComponentID::SCRIPT:
		{
			return GenerateComponentTable(S, this->_Scene->GetComponent<Script>(this->_Entity, I));
		}
		break;
		case LuaComponentID::TAG:
		{
			return GenerateComponentTable(S, this->_Scene->GetComponent<Tag>(this->_Entity, I));
		}
		break;
		case LuaComponentID::TRANSFORM:
		{
			return GenerateComponentTable(S, this->_Scene->GetComponent<Transform>(this->_Entity, I));
		}
		break;
		default:
		{
			VOLUND_ERROR("Unknown Component type (%d)!", Component);
		}
		break;
		}

		return sol::make_object(S, VL::Component());
	}

	void LuaEntity::Destroy(sol::this_state S)
	{
		this->_Scene->DestroyEntity(this->_Entity);
	}

	LuaEntity::LuaEntity(Scene* ThisScene, Entity entity)
	{
		this->_Scene = ThisScene;
		this->_Entity = entity;
	}

	LuaEntity::LuaEntity(Scene* ThisScene) : _Scene(ThisScene)
	{
		this->_Entity = this->_Scene->CreateEntity();
	}
}