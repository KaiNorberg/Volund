#include "PCH/PCH.h"
#include "Lua.h"

#include "Scene/Component/Components.h"
#include "Lua/LuaComponent/LuaComponents.h"

#include "Lua/LuaInput/LuaInput.h"
#include "Lua/LuaEntity/LuaEntity.h"

#include "Filesystem/Filesystem.h"

namespace Volund
{
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
}