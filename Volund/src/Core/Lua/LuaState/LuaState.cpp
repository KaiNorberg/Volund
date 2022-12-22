#include "PCH/PCH.h"
#include "LuaState.h"

#include "Core/Scene/Component/Components.h"

#include "Core/Lua/LuaComponent/LuaComponents.h"
#include "Core/Lua/LuaInput/LuaInput.h"
#include "Core/Lua/LuaEntity/LuaEntity.h"
#include "Core/Lua/LuaWindow/LuaWindow.h"
#include "Core/Lua/LuaVec/LuaVec.h"
#include "Core/Lua/LuaScene/LuaScene.h"

#include "Filesystem/Filesystem.h"

#include "Core/Scene/Scene.h"
#include "Core/Scene/Component/Components.h"

#include "Renderer/Material/Material.h"
#include "Renderer/Mesh/Mesh.h"

#include "Core/Window/Window.h"

namespace Volund
{
	sol::object LuaState::LuaRequire(sol::this_state S, std::string Filepath)
	{
		std::string Source = Filesystem::LoadFile(Filepath);

		sol::state_view State = S;
		return State.require_script(Filepath, Source);
	}

	void LuaState::LuaPrint(std::string String)
	{
		VOLUND_INFO(String.c_str());		
	}

	Ref<Scene> LuaState::GetScene()
	{
		return this->_ThisScene;
	}

	void LuaState::ScriptFile(const std::string& Filepath)
	{
		this->_SolState.script_file(Filepath);
	}

	void LuaState::OnEvent(Event* E)
	{
		this->_Input->HandleEvent(E);

		if (this->_ThisScene != nullptr)
		{
			this->_ThisScene->OnEvent(E);
		}
	}

	void LuaState::OnUpdate(TimeStep TS)
	{
		if (this->_ThisScene != nullptr)
		{
			this->_ThisScene->OnUpdate(TS);
		}
	}

	void LuaState::OnRender()
	{
		if (this->_ThisScene != nullptr)
		{
			this->_ThisScene->OnRender();
		}
	}

	LuaState::LuaState(Ref<Scene> ThisScene, Ref<Window> ThisWindow)
	{
		VOLUND_PROFILE_FUNCTION();

		this->_ThisScene = ThisScene;
		this->_Input = std::make_shared<Input>();

		this->_SolState.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string, sol::lib::utf8, sol::lib::os, sol::lib::table, sol::lib::io, sol::lib::package);

		this->CreateUserTypes();

		this->_SolState["Scene"] = LuaScene(ThisScene);
		this->_SolState["Input"] = LuaInput(this->_Input);
		this->_SolState["Window"] = LuaWindow(ThisWindow);

		this->_SolState["require"] = LuaRequire;
		this->_SolState["Print"] = LuaPrint;

		this->_SolState["Component"] = this->_SolState.create_table_with(
			"CAMERA", LuaComponent::CAMERA,
			"CAMERA_MOVEMENT", LuaComponent::CAMERA_MOVEMENT,
			"MESH_RENDERER", LuaComponent::MESH_RENDERER,
			"POINT_LIGHT", LuaComponent::POINT_LIGHT,
			"SCRIPT", LuaComponent::SCRIPT,
			"TAG", LuaComponent::TAG,
			"TRANSFORM", LuaComponent::TRANSFORM
		);

		this->_SolState["CursorMode"] = this->_SolState.create_table_with(
			"NORMAL", CursorMode::NORMAL,
			"HIDDEN", CursorMode::HIDDEN,
			"DISABLED", CursorMode::DISABLED,
			"CAPTURED", CursorMode::CAPTURED
		);
	}

	void LuaState::CreateUserTypes()
	{
		this->_SolState.new_usertype<LuaEntity>("VOLUND_ENTITY",
			"AddComponent", &LuaEntity::AddComponent,
			"DeleteComponent", &LuaEntity::DeleteComponent,
			"GetComponent", &LuaEntity::GetComponent,
			"Destroy", &LuaEntity::Destroy);

		this->_SolState.new_usertype<LuaCamera>("VOLUND_CAMERA",
			"GetFOV", &LuaCamera::GetFOV,
			"SetFOV", &LuaCamera::SetFOV,
			"GetNearPlane", &LuaCamera::GetNearPlane,
			"SetNearPlane", &LuaCamera::SetNearPlane,
			"GetFarPlane", &LuaCamera::GetFarPlane,
			"SetFarPlane", &LuaCamera::SetFarPlane,
			"IsActive", &LuaCamera::IsActive,
			"SetActive", &LuaCamera::SetActive);

		this->_SolState.new_usertype<LuaCameraMovement>("VOLUND_CAMERA_MOVEMENT",
			"GetSpeed", &LuaCameraMovement::GetSpeed,
			"SetSpeed", &LuaCameraMovement::SetSpeed,
			"SetSensitivity", &LuaCameraMovement::SetSensitivity,
			"GetSensitivity", &LuaCameraMovement::GetSensitivity);

		this->_SolState.new_usertype<LuaMeshRenderer>("VOLUND_MESH_RENDERER",
			"SetMesh", &LuaMeshRenderer::SetMesh,
			"SetMaterial", &LuaMeshRenderer::SetMaterial,
			"GetMesh", &LuaMeshRenderer::GetMesh,
			"GetMaterial", &LuaMeshRenderer::GetMaterial);

		this->_SolState.new_usertype<LuaPointLight>("VOLUND_POINT_LIGHT",
			"SetColor", &LuaPointLight::SetColor,
			"GetColor", &LuaPointLight::GetColor,
			"SetBrightness", &LuaPointLight::SetBrightness,
			"GetBrightness", &LuaPointLight::GetBrightness);

		this->_SolState.new_usertype<LuaScript>("VOLUND_SCRIPT");

		this->_SolState.new_usertype<LuaTag>("VOLUND_TAG",
			"Get", &LuaTag::Get,
			"Set", &LuaTag::Set);

		this->_SolState.new_usertype<LuaTransform>("VOLUND_TRANSFORM",
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

		this->_SolState.new_usertype<LuaScene>("VOLUND_SCENE",
			"CreateEntity", &LuaScene::CreateEntity);

		this->_SolState.new_usertype<LuaInput>("VOLUND_INPUT",
			"IsHeld", &LuaInput::IsHeld,
			"IsPressed", &LuaInput::IsPressed,
			"IsMouseButtonHeld", &LuaInput::IsMouseButtonHeld,
			"IsMouseButtonPressed", &LuaInput::IsMouseButtonPressed,
			"GetScrollPosition", &LuaInput::GetScrollPosition,
			"GetMousePosition", &LuaInput::GetMousePosition);

		this->_SolState.new_usertype<LuaWindow>("VOLUND_WINDOW",
			"SetCursorMode", &LuaWindow::SetCursorMode,
			"SetTitle", &LuaWindow::SetTitle,
			"SetVsync", &LuaWindow::SetVsync);

		this->_SolState.new_usertype<LuaVec4>("Vec4", sol::constructors<void(), void(float), void(float, float, float, float)>(),
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

		this->_SolState.new_usertype<LuaVec3>("Vec3", sol::constructors<void(), void(float), void(float, float, float)>(),
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

		this->_SolState.new_usertype<LuaVec2>("Vec2", sol::constructors<void(), void(float), void(float, float)>(),
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

		this->_SolState.new_usertype<LuaTexture>("Texture", sol::constructors<void(const std::string&)>());

		this->_SolState.new_usertype<LuaMesh>("Mesh", sol::constructors<void(const std::string&)>());

		this->_SolState.new_usertype<LuaShader>("Shader", sol::constructors<void(const std::string&)>());

		this->_SolState.new_usertype<LuaMaterial>("Material", sol::constructors<void(LuaShader)>(),
			"SetInt", &LuaMaterial::SetInt,
			"SetFloat", &LuaMaterial::SetFloat,
			"SetDouble", &LuaMaterial::SetDouble,
			"SetVec2", &LuaMaterial::SetVec2,
			"SetVec3", &LuaMaterial::SetVec3,
			"SetTexture", &LuaMaterial::SetTexture);
	}
}