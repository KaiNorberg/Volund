#include "PCH/PCH.h"
#include "Lua.h"

#include "Scene/Component/Components.h"

#include "Filesystem/Filesystem.h"

namespace Volund
{
	bool Lua::LuaInput::IsHeld(char KeyCode) const
	{
		return Scene::GetInput().IsHeld(KeyCode);
	}

	bool Lua::LuaInput::IsPressed(char KeyCode)
	{
		return Scene::GetInput().IsPressed(KeyCode);
	}

	bool Lua::LuaInput::IsMouseButtonHeld(char Button) const
	{
		return Scene::GetInput().IsMouseButtonHeld(Button);
	}

	bool Lua::LuaInput::IsMouseButtonPressed(char Button)
	{
		return Scene::GetInput().IsMouseButtonPressed(Button);
	}

	uint32_t Lua::LuaInput::GetScrollPosition() const
	{
		return Scene::GetInput().GetScrollPosition();
	}

	Vec2 Lua::LuaInput::GetMousePosition() const
	{
		return Scene::GetInput().GetMousePosition();
	}

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

	sol::object Lua::LuaEntity::GetComponent(sol::this_state S, LuaComponent Component, uint64_t I)
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

	Lua::LuaEntity::LuaEntity(Entity Entity)
	{
		this->_Entity = Entity;
	}

	Lua::LuaEntity::LuaEntity()
	{
		this->_Entity = VL::Scene::CreateEntity();
	}

	Ref<Material> Lua::LuaMaterial::Get()
	{
		return this->_Material;
	}

	void Lua::LuaMaterial::SetInt(const std::string& Name, lua_Integer Value)
	{
		this->_Material->Set(Name, (int)Value);
	}

	void Lua::LuaMaterial::SetFloat(const std::string& Name, float Value)
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

	Lua::LuaMaterial::LuaMaterial(Ref<Material> Material)
	{
		this->_Material = Material;
	}

	Lua::LuaMaterial::LuaMaterial(const std::string& ShaderPath)
	{
		auto NewShader = Shader::Create(ShaderPath);

		this->_Material = Material::Create(NewShader);
	}

	void Lua::Connect(sol::state& Lua)
	{
		Lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string, sol::lib::io, sol::lib::package);

		Lua["VolundRequire"] = LuaRequire;
		Lua["VolundPrint"] = LuaPrint;

		Lua.new_usertype<Vec4>("Vec4", sol::constructors<void(), void(float), void(float, float, float, float)>(), "x", &Vec4::x, "y", &Vec4::y, "z", &Vec4::z, "w", &Vec4::w);
		Lua.new_usertype<Vec3>("Vec3", sol::constructors<void(), void(float), void(float, float, float)>(), "x", &Vec3::x, "y", &Vec3::y, "z", &Vec3::z);
		Lua.new_usertype<Vec2>("Vec2", sol::constructors<void(), void(float), void(float, float)>(), "x", &Vec2::x, "y", &Vec2::y);
		
		Lua.new_usertype<LuaInput>("VolundInput",
			"IsHeld", &LuaInput::IsHeld,
			"IsPressed", &LuaInput::IsPressed,
			"IsMouseButtonHeld", &LuaInput::IsMouseButtonHeld,
			"IsMouseButtonPressed", &LuaInput::IsMouseButtonPressed,
			"GetScrollPosition", &LuaInput::GetScrollPosition,
			"GetMousePosition", &LuaInput::GetMousePosition);

		Lua["Input"] = LuaInput();

		Lua.new_usertype<LuaMaterial>("Material", sol::constructors<void(const std::string&)>(),
			"SetInt", &LuaMaterial::SetInt, 
			"SetFloat", &LuaMaterial::SetFloat, 
			"SetDouble", &LuaMaterial::SetDouble,
			"SetVec2", &LuaMaterial::SetVec2,
			"SetVec3", &LuaMaterial::SetVec3);

		Lua.new_usertype<LuaMesh>("Mesh", sol::constructors<void(const std::string&)>());

		Lua.new_usertype<LuaEntity>("Entity", sol::constructors<void()>(),
			"AddComponent", &LuaEntity::AddComponent,
			"DeleteComponent", &LuaEntity::DeleteComponent,
			"GetComponent", &LuaEntity::GetComponent);

		Lua.new_usertype<LuaCamera>("Camera",
			"GetFOV", &LuaCamera::GetFOV,
			"SetFOV", &LuaCamera::SetFOV,
			"GetNearPlane", &LuaCamera::GetNearPlane,
			"SetNearPlane", &LuaCamera::SetNearPlane,
			"GetFarPlane", &LuaCamera::GetFarPlane,
			"SetFarPlane", &LuaCamera::SetFarPlane,
			"IsActive", &LuaCamera::IsActive,
			"SetActive", &LuaCamera::SetActive);

		Lua.new_usertype<LuaCameraMovement>("CameraMovement",
			"GetSpeed", &LuaCameraMovement::GetSpeed,
			"SetSpeed", &LuaCameraMovement::SetSpeed,
			"SetSensitivity", &LuaCameraMovement::SetSensitivity,
			"GetSensitivity", &LuaCameraMovement::GetSensitivity);

		Lua.new_usertype<LuaMeshRenderer>("MeshRenderer",
			"SetMesh", &LuaMeshRenderer::SetMesh,
			"SetMaterial", &LuaMeshRenderer::SetMaterial,
			"GetMesh", &LuaMeshRenderer::GetMesh,
			"GetMaterial", &LuaMeshRenderer::GetMaterial);

		Lua.new_usertype<LuaPointLight>("PointLight",
			"SetColor", &LuaPointLight::SetColor,
			"GetColor", &LuaPointLight::GetColor,
			"SetBrightness", &LuaPointLight::SetBrightness,
			"GetBrightness", &LuaPointLight::GetBrightness);

		Lua.new_usertype<LuaScript>("Script");

		Lua.new_usertype<LuaTag>("Tag",
			"Get", &LuaTag::Get,
			"Set", &LuaTag::Set);

		Lua.new_usertype<LuaTransform>("Transform",
			"SetPosition", &LuaTransform::SetPosition,
			"GetPosition", &LuaTransform::GetPosition,
			"AddPosition", &LuaTransform::AddPosition,
			"SetRotation", &LuaTransform::SetRotation,
			"GetRotation", &LuaTransform::GetRotation,
			"AddRotation", &LuaTransform::AddRotation,
			"SetScale", &LuaTransform::SetScale,
			"GetScale", &LuaTransform::GetScale,
			"AddScale", &LuaTransform::AddScale,
			"GetFront", &LuaTransform::GetFront,
			"GetRight", &LuaTransform::GetRight,
			"GetUp", &LuaTransform::GetUp);

		Lua["Component"] = Lua.create_table_with(
			"CAMERA", LuaComponent::CAMERA,
			"CAMERA_MOVEMENT", LuaComponent::CAMERA_MOVEMENT,
			"MESH_RENDERER", LuaComponent::MESH_RENDERER,
			"POINT_LIGHT", LuaComponent::POINT_LIGHT,
			"SCRIPT", LuaComponent::SCRIPT,
			"TAG", LuaComponent::TAG,
			"TRANSFORM", LuaComponent::TRANSFORM
		);
	}

	sol::object Lua::LuaRequire(sol::this_state S, std::string Filepath)
	{
		std::string Source = Filesystem::LoadFile(Filepath);

		sol::state_view State = S;
		return State.require_script(Filepath, Source);
	}

	void Lua::LuaPrint(std::string String)
	{
		VOLUND_INFO(String.c_str());		
	}

	Ref<Mesh> Lua::LuaMesh::Get()
	{
		return this->_Mesh;
	}

	Lua::LuaMesh::LuaMesh(Ref<Mesh> Mesh)
	{
		this->_Mesh = Mesh;
	}

	Lua::LuaMesh::LuaMesh(const std::string& MeshPath)
	{
		this->_Mesh = Mesh::Create(MeshPath);
	}

	float Lua::LuaCamera::GetFOV()
	{
		return this->_Camera->FOV;
	}

	void Lua::LuaCamera::SetFOV(float FOV)
	{
		this->_Camera->FOV = FOV;
	}

	float Lua::LuaCamera::GetNearPlane()
	{
		return this->_Camera->NearPlane;
	}

	void Lua::LuaCamera::SetNearPlane(float NearPlane)
	{
		this->_Camera->NearPlane = NearPlane;
	}

	float Lua::LuaCamera::GetFarPlane()
	{
		return this->_Camera->FarPlane;
	}

	void Lua::LuaCamera::SetFarPlane(float FarPlane)
	{
		this->_Camera->FarPlane = FarPlane;
	}

	bool Lua::LuaCamera::IsActive()
	{
		return this->_Camera->IsActive();
	}

	void Lua::LuaCamera::SetActive()
	{
		this->_Camera->SetActive();
	}

	Lua::LuaCamera::LuaCamera(Ref<Camera> Camera)
	{
		this->_Camera = Camera;
	}

	float Lua::LuaCameraMovement::GetSpeed()
	{
		return this->_CameraMovement->Speed;
	}

	void Lua::LuaCameraMovement::SetSpeed(float Speed)
	{
		this->_CameraMovement->Speed = Speed;
	}
	
	float Lua::LuaCameraMovement::GetSensitivity()
	{
		return this->_CameraMovement->Sensitivity;
	}

	void Lua::LuaCameraMovement::SetSensitivity(float Sensitivity)
	{
		this->_CameraMovement->Sensitivity = Sensitivity;
	}

	Lua::LuaCameraMovement::LuaCameraMovement(Ref<CameraMovement> CameraMovement)
	{
		this->_CameraMovement = CameraMovement;
	}

	void Lua::LuaMeshRenderer::SetMesh(LuaMesh NewMesh)
	{
		this->_MeshRenderer->SetMesh(NewMesh.Get());
	}

	void Lua::LuaMeshRenderer::SetMaterial(LuaMaterial NewMaterial)
	{
		this->_MeshRenderer->SetMaterial(NewMaterial.Get());
	}

	Lua::LuaMesh Lua::LuaMeshRenderer::GetMesh()
	{
		return LuaMesh(this->_MeshRenderer->GetMesh());
	}

	Lua::LuaMaterial Lua::LuaMeshRenderer::GetMaterial()
	{
		return LuaMaterial(this->_MeshRenderer->GetMaterial());
	}

	Lua::LuaMeshRenderer::LuaMeshRenderer(Ref<MeshRenderer> MeshRenderer)
	{
		this->_MeshRenderer = MeshRenderer;
	}

	Vec3 Lua::LuaPointLight::GetColor()
	{
		return this->_PointLight->Color;
	}

	void Lua::LuaPointLight::SetColor(Vec3 Color)
	{
		this->_PointLight->Color = Color;
	}
	
	void Lua::LuaPointLight::SetBrightness(float Brightness)
	{
		this->_PointLight->Brightness = Brightness;
	}

	float Lua::LuaPointLight::GetBrightness()
	{
		return this->_PointLight->Brightness;
	}

	Lua::LuaPointLight::LuaPointLight(Ref<PointLight> PointLight)
	{
		this->_PointLight = PointLight;
	}

	Lua::LuaScript::LuaScript(Ref<Script> Script)
	{
		this->_Script = Script;
	}

	std::string Lua::LuaTag::Get()
	{
		return this->_Tag->String;
	}

	void Lua::LuaTag::Set(std::string String)
	{
		this->_Tag->String = String;
	}
	
	Lua::LuaTag::LuaTag(Ref<Tag> Tag)
	{
		this->_Tag = Tag;
	}

	void Lua::LuaTransform::SetPosition(const Vec3& Position)
	{
		this->_Transform->Position = Position;
	}

	Vec3 Lua::LuaTransform::GetPosition() const
	{
		return this->_Transform->Position;
	}

	void Lua::LuaTransform::AddPosition(const Vec3& Position)
	{
		this->_Transform->Position += Position;
	}

	void Lua::LuaTransform::SetRotation(const Vec3& Rotation)
	{
		this->_Transform->SetRotation(Rotation);
	}

	Vec3 Lua::LuaTransform::GetRotation() const
	{
		return this->_Transform->GetRotation();
	}

	void Lua::LuaTransform::AddRotation(const Vec3& Rotation)
	{
		this->_Transform->AddRotation(Rotation);
	}

	void Lua::LuaTransform::SetScale(const Vec3& Scale)
	{
		this->_Transform->Scale = Scale;
	}

	Vec3 Lua::LuaTransform::GetScale() const
	{
		return this->_Transform->Scale;
	}

	void Lua::LuaTransform::AddScale(const Vec3& Scale)
	{
		this->_Transform->Scale += Scale;
	}

	Vec3 Lua::LuaTransform::GetFront() const
	{
		return this->_Transform->GetFront();
	}

	Vec3 Lua::LuaTransform::GetRight() const
	{
		return this->_Transform->GetRight();
	}

	Vec3 Lua::LuaTransform::GetUp() const
	{
		return this->_Transform->GetUp();
	}

	Lua::LuaTransform::LuaTransform(Ref<Transform> Transform)
	{
		this->_Transform = Transform;
	}
}