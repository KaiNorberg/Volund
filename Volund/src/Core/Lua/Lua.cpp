#include "PCH/PCH.h"
#include "Lua.h"

#include "Core/Scene/Component/Components.h"

#include "Core/Lua/LuaComponent/LuaComponents.h"
#include "Core/Lua/LuaInput/LuaInput.h"
#include "Core/Lua/LuaEntity/LuaEntity.h"
#include "Core/Lua/LuaWindow/LuaWindow.h"
#include "Core/Lua/LuaVec/LuaVec.h"

#include "Filesystem/Filesystem.h"

namespace Volund
{
	void Lua::Connect(sol::state& Lua)
	{
		Lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string, sol::lib::utf8, sol::lib::os, sol::lib::table, sol::lib::io, sol::lib::package);

		Lua["require"] = LuaRequire;
		Lua["Print"] = LuaPrint;

		Lua.new_usertype<LuaInput>("VolundInput",
			"IsHeld", &LuaInput::IsHeld,
			"IsPressed", &LuaInput::IsPressed,
			"IsMouseButtonHeld", &LuaInput::IsMouseButtonHeld,
			"IsMouseButtonPressed", &LuaInput::IsMouseButtonPressed,
			"GetScrollPosition", &LuaInput::GetScrollPosition,
			"GetMousePosition", &LuaInput::GetMousePosition);

		Lua["Input"] = LuaInput();

		Lua.new_usertype<LuaWindow>("VolundWindow",
			"SetCursorMode", &LuaWindow::SetCursorMode,
			"SetTitle", &LuaWindow::SetTitle,
			"SetVsync", &LuaWindow::SetVsync);

		Lua["Window"] = LuaWindow();

		Lua.new_usertype<LuaVec4>("Vec4", sol::constructors<void(), void(float), void(float, float, float, float)>(),
			"x", &LuaVec4::x,
			"y", &LuaVec4::y,
			"z", &LuaVec4::z,
			"w", &LuaVec4::w,
			sol::meta_function::addition, sol::resolve<LuaVec4(float)>(&LuaVec4::operator+),
			sol::meta_function::addition, sol::resolve<LuaVec4(const LuaVec4&)>(&LuaVec4::operator+),
			sol::meta_function::subtraction, sol::resolve<LuaVec4(float)>(&LuaVec4::operator-),
			sol::meta_function::subtraction, sol::resolve<LuaVec4(const LuaVec4&)>(&LuaVec4::operator-),
			sol::meta_function::multiplication, sol::resolve<LuaVec4(float)>(&LuaVec4::operator*),
			sol::meta_function::multiplication, sol::resolve<LuaVec4(const LuaVec4&)>(&LuaVec4::operator*),
			sol::meta_function::division, sol::resolve<LuaVec4(float)>(&LuaVec4::operator/),
			sol::meta_function::division, sol::resolve<LuaVec4(const LuaVec4&)>(&LuaVec4::operator/));

		Lua.new_usertype<LuaVec3>("Vec3", sol::constructors<void(), void(float), void(float, float, float)>(),
			"x", &LuaVec3::x,
			"y", &LuaVec3::y,
			"z", &LuaVec3::z,
			sol::meta_function::addition, sol::resolve<LuaVec3(float)>(&LuaVec3::operator+),
			sol::meta_function::addition, sol::resolve<LuaVec3(const LuaVec3&)>(&LuaVec3::operator+),
			sol::meta_function::subtraction, sol::resolve<LuaVec3(float)>(&LuaVec3::operator-),
			sol::meta_function::subtraction, sol::resolve<LuaVec3(const LuaVec3&)>(&LuaVec3::operator-),
			sol::meta_function::multiplication, sol::resolve<LuaVec3(float)>(&LuaVec3::operator*),
			sol::meta_function::multiplication, sol::resolve<LuaVec3(const LuaVec3&)>(&LuaVec3::operator*),
			sol::meta_function::division, sol::resolve<LuaVec3(float)>(&LuaVec3::operator/),
			sol::meta_function::division, sol::resolve<LuaVec3(const LuaVec3&)>(&LuaVec3::operator/));

		Lua.new_usertype<LuaVec2>("Vec2", sol::constructors<void(), void(float), void(float, float)>(),
			"x", &LuaVec2::x,
			"y", &LuaVec2::y,
			sol::meta_function::addition, sol::resolve<LuaVec2(float)>(&LuaVec2::operator+),
			sol::meta_function::addition, sol::resolve<LuaVec2(const LuaVec2&)>(&LuaVec2::operator+),
			sol::meta_function::subtraction, sol::resolve<LuaVec2(float)>(&LuaVec2::operator-),
			sol::meta_function::subtraction, sol::resolve<LuaVec2(const LuaVec2&)>(&LuaVec2::operator-),
			sol::meta_function::multiplication, sol::resolve<LuaVec2(float)>(&LuaVec2::operator*),
			sol::meta_function::multiplication, sol::resolve<LuaVec2(const LuaVec2&)>(&LuaVec2::operator*),
			sol::meta_function::division, sol::resolve<LuaVec2(float)>(&LuaVec2::operator/),
			sol::meta_function::division, sol::resolve<LuaVec2(const LuaVec2&)>(&LuaVec2::operator/));

		Lua.new_usertype<LuaTexture>("Texture", sol::constructors<void(const std::string&)>());

		Lua.new_usertype<LuaMesh>("Mesh", sol::constructors<void(const std::string&)>());

		Lua.new_usertype<LuaShader>("Shader", sol::constructors<void(const std::string&)>());

		Lua.new_usertype<LuaMaterial>("Material", sol::constructors<void(LuaShader)>(),
			"SetInt", &LuaMaterial::SetInt,
			"SetFloat", &LuaMaterial::SetFloat,
			"SetDouble", &LuaMaterial::SetDouble,
			"SetVec2", &LuaMaterial::SetVec2,
			"SetVec3", &LuaMaterial::SetVec3,
			"SetTexture", &LuaMaterial::SetTexture);

		Lua.new_usertype<LuaEntity>("Entity", sol::constructors<void()>(),
			"AddComponent", &LuaEntity::AddComponent,
			"DeleteComponent", &LuaEntity::DeleteComponent,
			"GetComponent", &LuaEntity::GetComponent,
			"Destroy", &LuaEntity::Destroy);

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

		Lua["CursorMode"] = Lua.create_table_with(
			"NORMAL", CursorMode::NORMAL,
			"HIDDEN", CursorMode::HIDDEN,
			"DISABLED", CursorMode::DISABLED,
			"CAPTURED", CursorMode::CAPTURED
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