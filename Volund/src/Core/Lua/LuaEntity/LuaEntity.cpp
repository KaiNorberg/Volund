#include "PCH/PCH.h"
#include "LuaEntity.h"

#include "Core/Scene/Component/Components.h"

#include "Core/Lua/LuaMaterial/LuaMaterial.h"
#include "Core/Lua/LuaMesh/LuaMesh.h"

namespace Volund
{
	void LuaEntity::AddComponent(LuaComponent Component, const sol::table& Table)
	{
		if (!VL::Scene::HasEntity(this->_Entity))
		{
			VOLUND_WARNING("Invalid this->_Entity %d!", this->_Entity);

			return;
		}

		switch (Component)
		{
		case LuaComponent::CAMERA:
		{
			auto NewComponent = VL::Scene::CreateComponent<Camera>(this->_Entity);

			if (Table["IsActive"] != sol::lua_nil && Table["IsActive"])
			{
				NewComponent->SetActive();
			}

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
		case LuaComponent::CAMERA_MOVEMENT:
		{
			auto NewComponent = VL::Scene::CreateComponent<CameraMovement>(this->_Entity);

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
		case LuaComponent::MESH_RENDERER:
		{
			if (Table["Mesh"] != sol::lua_nil && Table["Material"] != sol::lua_nil)
			{
				LuaMesh MeshAsset = Table["Mesh"];
				LuaMaterial MaterialAsset = Table["Material"];

				VL::Scene::CreateComponent<MeshRenderer>(this->_Entity, MeshAsset.Get(), MaterialAsset.Get());
			}
			else
			{
				VOLUND_WARNING("Unable to read mesh or material from MeshRenderer table!");
			}
		}
		break;
		case LuaComponent::POINT_LIGHT:
		{
			auto NewComponent = VL::Scene::CreateComponent<PointLight>(this->_Entity);

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
		case LuaComponent::SCRIPT:
		{
			sol::function OnCreate = Table["OnCreate"];
			sol::function OnUpdate = Table["OnUpdate"];
			sol::function OnDelete = Table["OnDelete"];

			auto NewComponent = VL::Scene::CreateComponent<Script>(this->_Entity, OnCreate, OnUpdate, OnDelete);
		}
		break;
		case LuaComponent::TAG:
		{
			std::string String = Table["String"];

			auto NewComponent = VL::Scene::CreateComponent<Tag>(this->_Entity, String);
		}
		break;
		case LuaComponent::TRANSFORM:
		{
			auto NewComponent = VL::Scene::CreateComponent<Transform>(this->_Entity);

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
			VOLUND_ERROR("Unknown Component type (%d)!", Component);
		}
		break;
		}
	}

	void LuaEntity::DeleteComponent(LuaComponent Component, uint64_t I)
	{
		if (!VL::Scene::HasEntity(this->_Entity))
		{
			VOLUND_WARNING("Invalid this->_Entity %d!", this->_Entity);

			return;
		}

		switch (Component)
		{
		case LuaComponent::CAMERA:
		{
			VL::Scene::DeleteComponent<Camera>(this->_Entity, I);
		}
		break;
		case LuaComponent::CAMERA_MOVEMENT:
		{
			VL::Scene::DeleteComponent<CameraMovement>(this->_Entity, I);
		}
		break;
		case LuaComponent::MESH_RENDERER:
		{
			VL::Scene::DeleteComponent<MeshRenderer>(this->_Entity, I);
		}
		break;
		case LuaComponent::POINT_LIGHT:
		{
			VL::Scene::DeleteComponent<PointLight>(this->_Entity, I);
		}
		break;
		case LuaComponent::SCRIPT:
		{
			VL::Scene::DeleteComponent<Script>(this->_Entity, I);
		}
		break;
		case LuaComponent::TAG:
		{
			VL::Scene::DeleteComponent<Tag>(this->_Entity, I);
		}
		break;
		case LuaComponent::TRANSFORM:
		{
			VL::Scene::DeleteComponent<Transform>(this->_Entity, I);
		}
		break;
		default:
		{
			VOLUND_ERROR("Unknown Component type (%d)!", Component);
		}
		break;
		}
	}

	sol::object LuaEntity::GetComponent(sol::this_state S, LuaComponent Component, uint64_t I)
	{
		if (!VL::Scene::HasEntity(this->_Entity))
		{
			VOLUND_WARNING("Invalid this->_Entity %d!", this->_Entity);

			return sol::make_object(S, VL::Component());
		}

		switch (Component)
		{
		case LuaComponent::CAMERA:
		{
			return sol::make_object(S, *(VL::Scene::GetComponent<Camera>(this->_Entity, I).get()));
		}
		break;
		case LuaComponent::CAMERA_MOVEMENT:
		{
			return sol::make_object(S, *(VL::Scene::GetComponent<CameraMovement>(this->_Entity, I).get()));
		}
		break;
		case LuaComponent::MESH_RENDERER:
		{
			return sol::make_object(S, LuaMeshRenderer(VL::Scene::GetComponent<MeshRenderer>(this->_Entity, I)));
		}
		break;
		case LuaComponent::POINT_LIGHT:
		{
			return sol::make_object(S, *(VL::Scene::GetComponent<PointLight>(this->_Entity, I).get()));
		}
		break;
		case LuaComponent::SCRIPT:
		{
			return sol::make_object(S, *(VL::Scene::GetComponent<Script>(this->_Entity, I).get()));
		}
		break;
		case LuaComponent::TAG:
		{
			return sol::make_object(S, *(VL::Scene::GetComponent<Tag>(this->_Entity, I).get()));
		}
		break;
		case LuaComponent::TRANSFORM:
		{
			return sol::make_object(S, LuaTransform(VL::Scene::GetComponent<Transform>(this->_Entity, I)));
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

	LuaEntity::LuaEntity(Entity Entity)
	{
		this->_Entity = Entity;
	}

	LuaEntity::LuaEntity()
	{
		this->_Entity = VL::Scene::CreateEntity();
	}
}