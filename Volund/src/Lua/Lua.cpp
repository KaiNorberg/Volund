#include "PCH/PCH.h"
#include "Lua.h"

#include "Scene/Component/Components.h"

namespace Volund
{
	void Lua::LuaEntity::AddComponent(LuaComponent Component, const sol::table& Table)
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
			LuaMesh MeshAsset = Table["Mesh"];
			LuaMaterial MaterialAsset = Table["Material"];

			VL::Scene::CreateComponent<MeshRenderer>(this->_Entity, MeshAsset.Get(), MaterialAsset.Get());
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

	void Lua::LuaEntity::DeleteComponent(LuaComponent Component, uint64_t I)
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

	Lua::LuaEntity::LuaEntity()
	{
		this->_Entity = VL::Scene::CreateEntity();
	}

	Ref<Material> Lua::LuaMaterial::Get()
	{
		return this->_Material;
	}

	void Lua::LuaMaterial::SetInt(const std::string& Name, int32_t Value)
	{
		this->_Material->Set(Name, Value);
	}

	void Lua::LuaMaterial::SetDouble(const std::string& Name, double Value)
	{
		this->_Material->Set(Name, Value);
	}

	void Lua::LuaMaterial::SetVec2(const std::string& Name, Vec2 Value)
	{
		this->_Material->Set(Name, Value);
	}

	void Lua::LuaMaterial::SetVec3(const std::string& Name, Vec3 Value)
	{
		this->_Material->Set(Name, Value);
	}

	Lua::LuaMaterial::LuaMaterial(const std::string& ShaderPath)
	{
		auto NewShader = Shader::Create(ShaderPath);

		this->_Material = Material::Create(NewShader);
	}

	void Lua::Connect(sol::state& Lua)
	{
		Lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string, sol::lib::io);

		Lua.new_usertype<Vec4>("Vec4", sol::constructors<void(), void(float), void(float, float, float, float)>(), "x", &Vec4::x, "y", &Vec4::y, "z", &Vec4::z, "w", &Vec4::w);
		Lua.new_usertype<Vec3>("Vec3", sol::constructors<void(), void(float), void(float, float, float)>(), "x", &Vec3::x, "y", &Vec3::y, "z", &Vec3::z);
		Lua.new_usertype<Vec2>("Vec2", sol::constructors<void(), void(float), void(float, float)>(), "x", &Vec2::x, "y", &Vec2::y);

		Lua.new_usertype<LuaEntity>("Entity", sol::constructors<void()>(), "AddComponent", &LuaEntity::AddComponent, "DeleteComponent", &LuaEntity::DeleteComponent);

		Lua.new_usertype<LuaMaterial>("Material", sol::constructors<void(const std::string&)>(), "Set", &LuaMaterial::SetInt, "Set", &LuaMaterial::SetDouble,
			"Set", &LuaMaterial::SetVec2, "Set", &LuaMaterial::SetVec3);

		Lua.new_usertype<LuaMesh>("Mesh", sol::constructors<void(const std::string&)>());

		Lua["Component"] = Lua.create_table_with(
			"CAMERA", LuaComponent::CAMERA,
			"CAMERA_MOVEMENT", LuaComponent::CAMERA_MOVEMENT,
			"MESH_RENDERER", LuaComponent::MESH_RENDERER,
			"POINT_LIGHT", LuaComponent::POINT_LIGHT,
			"TAG", LuaComponent::TAG,
			"TRANSFORM", LuaComponent::TRANSFORM
		);
	}

	Ref<Mesh> Lua::LuaMesh::Get()
	{
		return this->_Mesh;
	}

	Lua::LuaMesh::LuaMesh(const std::string& MeshPath)
	{
		this->_Mesh = Mesh::Create(MeshPath);
	}
}