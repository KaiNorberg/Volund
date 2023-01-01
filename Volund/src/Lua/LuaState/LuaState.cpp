#include "PCH/PCH.h"
#include "LuaState.h"

#include "Scene/Component/Components.h"

#include "Lua/LuaInput/LuaInput.h"
#include "Lua/LuaEntity/LuaEntity.h"
#include "Lua/LuaWindow/LuaWindow.h"
#include "Lua/LuaVec/LuaVec.h"
#include "Lua/LuaScene/LuaScene.h"
#include "Lua/LuaMaterial/LuaMaterial.h"
#include "Lua/LuaMesh/LuaMesh.h"
#include "Lua/LuaShader/LuaShader.h"
#include "Lua/LuaTexture/LuaTexture.h"

#include "Filesystem/Filesystem.h"

#include "Scene/Scene.h"
#include "Scene/Component/Components.h"

#include "Renderer/Material/Material.h"
#include "Renderer/Mesh/Mesh.h"

#include "Window/Window.h"

namespace Volund
{
	sol::object LuaState::LuaRequire(sol::this_state S, std::string Filepath)
	{
		std::string Source = Filesystem::LoadFile(Filepath);

		sol::state_view State = S;
		return State.require_script(Filepath, Source);
	}

	void LuaState::LuaPrint(sol::object Object)
	{
		VOLUND_INFO(Object.as<std::string>().c_str());
	}

	Ref<Scene> LuaState::GetScene()
	{
		return this->_ThisScene;
	}

	void LuaState::ScriptFile(const std::string& Filepath)
	{
		this->_SolState.safe_script_file(Filepath, [](lua_State*, sol::protected_function_result pfr)
		{		
			sol::error err = pfr;
			VOLUND_WARNING(err.what());

			return pfr;
		});
	}

	void LuaState::Procedure(const Event& E)
	{
		if (this->_ThisScene != nullptr)
		{
			this->_Input->HandleEvent(E);

			this->_ThisScene->Procedure(E);
		}
	}

	LuaState::LuaState(Ref<Scene> ThisScene, Ref<Window> ThisWindow)
	{
		VOLUND_PROFILE_FUNCTION();

		ThisWindow->Reset();

		this->_ThisScene = ThisScene;
		this->_Input = std::make_shared<Input>();

		this->_SolState.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string, sol::lib::utf8, sol::lib::os, sol::lib::table, sol::lib::io, sol::lib::package);

		this->CreateUserTypes();

		this->_SolState["Scene"] = LuaScene(ThisScene);
		this->_SolState["Input"] = LuaInput(this->_Input);
		this->_SolState["Window"] = LuaWindow(ThisWindow);

		this->_SolState["require"] = LuaRequire;
		this->_SolState["print"] = LuaPrint;

		this->_SolState.new_enum("Component",
			"CAMERA", LuaComponentID::CAMERA,
			"CAMERA_MOVEMENT", LuaComponentID::CAMERA_MOVEMENT,
			"MESH_RENDERER", LuaComponentID::MESH_RENDERER,
			"POINT_LIGHT", LuaComponentID::POINT_LIGHT,
			"SCRIPT", LuaComponentID::SCRIPT,
			"TAG", LuaComponentID::TAG,
			"TRANSFORM", LuaComponentID::TRANSFORM
		);

		this->_SolState.new_enum("CursorMode",
			"NORMAL", CursorMode::NORMAL,
			"HIDDEN", CursorMode::HIDDEN,
			"DISABLED", CursorMode::DISABLED,
			"CAPTURED", CursorMode::CAPTURED
		);
	}

	LuaState::~LuaState()
	{
		this->_ThisScene.reset();
	}

	void LuaState::CreateUserTypes()
	{
		this->_SolState.new_usertype<LuaEntity>("VOLUND_ENTITY", sol::no_constructor,
			"Padding", &LuaEntity::Padding,
			"AddComponent", &LuaEntity::AddComponent,
			"DeleteComponent", &LuaEntity::DeleteComponent,
			"GetComponent", &LuaEntity::GetComponent,
			"HasComponent", &LuaEntity::HasComponent,
			"ComponentAmount", &LuaEntity::ComponentAmount,
			"Destroy", &LuaEntity::Destroy);

		this->_SolState.new_usertype<LuaScene>("VOLUND_SCENE", sol::no_constructor,
			"Padding", &LuaScene::Padding,
			"TimeSinceStart", &LuaScene::TimeSinceStart,
			"CreateEntity", &LuaScene::CreateEntity,
			"View", sol::overload(&LuaScene::ComponentView, &LuaScene::ScriptView));

		this->_SolState.new_usertype<LuaInput>("VOLUND_INPUT", sol::no_constructor,
			"Padding", &LuaInput::Padding,
			"IsHeld", &LuaInput::IsHeld,
			"IsPressed", &LuaInput::IsPressed,
			"IsMouseButtonHeld", &LuaInput::IsMouseButtonHeld,
			"IsMouseButtonPressed", &LuaInput::IsMouseButtonPressed,
			"GetScrollPosition", &LuaInput::GetScrollPosition,
			"GetMousePosition", &LuaInput::GetMousePosition);

		this->_SolState.new_usertype<LuaWindow>("VOLUND_WINDOW", sol::no_constructor,
			"SetCursorMode", &LuaWindow::SetCursorMode,
			"SetTitle", &LuaWindow::SetTitle,
			"SetVsync", &LuaWindow::SetVsync);

		this->_SolState.new_usertype<LuaVec4>("Vec4", sol::constructors<void(LuaVec4), void(), void(float), void(float, float, float, float)>(),
			"x", &LuaVec4::x,
			"y", &LuaVec4::y,
			"z", &LuaVec4::z,
			"w", &LuaVec4::w,
			"Length", &LuaVec4::Length,
			"Normalize", &LuaVec4::Normalize,
			sol::meta_function::addition,		sol::overload(sol::resolve<LuaVec4(const LuaVec4&)>(&LuaVec4::operator+), sol::resolve<LuaVec4(float)>(&LuaVec4::operator+)),
			sol::meta_function::subtraction,	sol::overload(sol::resolve<LuaVec4(const LuaVec4&)>(&LuaVec4::operator-), sol::resolve<LuaVec4(float)>(&LuaVec4::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<LuaVec4(const LuaVec4&)>(&LuaVec4::operator*), sol::resolve<LuaVec4(float)>(&LuaVec4::operator*)),
			sol::meta_function::division,		sol::overload(sol::resolve<LuaVec4(const LuaVec4&)>(&LuaVec4::operator/), sol::resolve<LuaVec4(float)>(&LuaVec4::operator/)));

		this->_SolState.new_usertype<LuaVec3>("Vec3", sol::constructors<void(LuaVec3), void(), void(float), void(float, float, float)>(),
			"x", &LuaVec3::x,
			"y", &LuaVec3::y,
			"z", &LuaVec3::z,
			"Length", &LuaVec3::Length,
			"Normalize", &LuaVec3::Normalize,
			"Cross", &LuaVec3::Cross,
			sol::meta_function::addition,		sol::overload(sol::resolve<LuaVec3(const LuaVec3&)>(&LuaVec3::operator+), sol::resolve<LuaVec3(float)>(&LuaVec3::operator+)),
			sol::meta_function::subtraction,	sol::overload(sol::resolve<LuaVec3(const LuaVec3&)>(&LuaVec3::operator-), sol::resolve<LuaVec3(float)>(&LuaVec3::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<LuaVec3(const LuaVec3&)>(&LuaVec3::operator*), sol::resolve<LuaVec3(float)>(&LuaVec3::operator*)),
			sol::meta_function::division,		sol::overload(sol::resolve<LuaVec3(const LuaVec3&)>(&LuaVec3::operator/), sol::resolve<LuaVec3(float)>(&LuaVec3::operator/)));

		this->_SolState.new_usertype<LuaVec2>("Vec2", sol::constructors<void(LuaVec2), void(), void(float), void(float, float)>(),
			"x", &LuaVec2::x,
			"y", &LuaVec2::y,
			"Length", &LuaVec2::Length,
			"Normalize", &LuaVec2::Normalize,
			sol::meta_function::addition,		sol::overload(sol::resolve<LuaVec2(const LuaVec2&)>(&LuaVec2::operator+), sol::resolve<LuaVec2(float)>(&LuaVec2::operator+)),
			sol::meta_function::subtraction,	sol::overload(sol::resolve<LuaVec2(const LuaVec2&)>(&LuaVec2::operator-), sol::resolve<LuaVec2(float)>(&LuaVec2::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<LuaVec2(const LuaVec2&)>(&LuaVec2::operator*), sol::resolve<LuaVec2(float)>(&LuaVec2::operator*)),
			sol::meta_function::division,		sol::overload(sol::resolve<LuaVec2(const LuaVec2&)>(&LuaVec2::operator/), sol::resolve<LuaVec2(float)>(&LuaVec2::operator/)));

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