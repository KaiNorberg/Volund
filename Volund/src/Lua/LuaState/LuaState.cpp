#include "PCH/PCH.h"
#include "LuaState.h"

#include "Scene/Component/Components.h"

#include "Lua/LuaEntity/LuaEntity.h"
#include "Lua/LuaVec/LuaVec.h"
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
			this->_ThisInput->HandleEvent(E);

			this->_ThisScene->Procedure(E);
		}
	}

	void LuaState::LuaPrint(sol::object Object)
	{
		VOLUND_INFO(Object.as<std::string>().c_str());
	}

	sol::object LuaState::LuaRequire(sol::this_state S, std::string Filepath)
	{
		std::string Source = Filesystem::LoadFile(Filepath);

		sol::state_view State = S;
		return State.require_script(Filepath, Source);
	}

	sol::table LuaState::LuaComponentView(sol::this_state S, Ref<Scene> ThisScene, LuaComponentID ComponentID)
	{
		switch (ComponentID)
		{
		case LuaComponentID::CAMERA:
		{
			return LuaState::GenerateComponentView<Camera>(S, ThisScene);
		}
		break;
		case LuaComponentID::CAMERA_MOVEMENT:
		{
			return LuaState::GenerateComponentView<CameraMovement>(S, ThisScene);
		}
		break;
		case LuaComponentID::MESH_RENDERER:
		{
			return LuaState::GenerateComponentView<MeshRenderer>(S, ThisScene);
		}
		break;
		case LuaComponentID::POINT_LIGHT:
		{
			return LuaState::GenerateComponentView<PointLight>(S, ThisScene);
		}
		break;
		case LuaComponentID::SCRIPT:
		{
			return LuaState::GenerateComponentView<Script>(S, ThisScene);
		}
		break;
		case LuaComponentID::TAG:
		{
			return LuaState::GenerateComponentView<Tag>(S, ThisScene);
		}
		break;
		case LuaComponentID::TRANSFORM:
		{
			return LuaState::GenerateComponentView<Transform>(S, ThisScene);
		}
		break;
		default:
		{
			VOLUND_ERROR("Unknown ComponentID type (%d)!", ComponentID);
		}
		break;
		}

		return 0;
	}

	sol::table LuaState::LuaScriptView(sol::this_state S, Ref<Scene> ThisScene, sol::table ScriptTable)
	{
		sol::state_view StateView = S;

		sol::table Output = StateView.create_table_with();

		std::vector<Ref<Script>> View;
		ThisScene->View(View);

		for (auto& Component : View)
		{
			if (Component->Compare(ScriptTable))
			{
				Output.add(Component->Table);
			}
		}

		return Output;
	}

	LuaState::LuaState(Ref<Scene> ThisScene, Ref<Window> ThisWindow)
	{
		VOLUND_PROFILE_FUNCTION();

		ThisWindow->Reset();

		auto ThisInput = std::make_shared<Input>();

		this->_ThisScene = ThisScene;
		this->_ThisInput = ThisInput;
		this->_ThisWindow = ThisWindow;

		this->_SolState.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string, sol::lib::utf8, sol::lib::os, sol::lib::table, sol::lib::io, sol::lib::package);

		//Functions

		this->_SolState["require"] = LuaRequire;
		this->_SolState["print"] = LuaPrint;

		//Usertypes

		this->_SolState.new_usertype<LuaEntity>("VOLUND_ENTITY", sol::no_constructor,
			"Padding", &LuaEntity::Padding,
			"AddComponent", &LuaEntity::AddComponent,
			"DeleteComponent", &LuaEntity::DeleteComponent,
			"GetComponent", &LuaEntity::GetComponent,
			"GetScript", &LuaEntity::GetScript,
			"HasComponent", &LuaEntity::HasComponent,
			"ComponentAmount", &LuaEntity::ComponentAmount
		);

		this->_SolState.new_usertype<LuaVec4>("Vec4", sol::constructors<void(LuaVec4), void(), void(float), void(float, float, float, float)>(),
			"x", &LuaVec4::x,
			"y", &LuaVec4::y,
			"z", &LuaVec4::z,
			"w", &LuaVec4::w,
			"Length", &LuaVec4::Length,
			"Length2", &LuaVec4::Length2,
			"Normalize", &LuaVec4::Normalize,
			"Reflect", &LuaVec4::Reflect,
			sol::meta_function::addition, sol::overload(sol::resolve<LuaVec4(const LuaVec4&)>(&LuaVec4::operator+), sol::resolve<LuaVec4(float)>(&LuaVec4::operator+)),
			sol::meta_function::subtraction, sol::overload(sol::resolve<LuaVec4(const LuaVec4&)>(&LuaVec4::operator-), sol::resolve<LuaVec4(float)>(&LuaVec4::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<LuaVec4(const LuaVec4&)>(&LuaVec4::operator*), sol::resolve<LuaVec4(float)>(&LuaVec4::operator*)),
			sol::meta_function::division, sol::overload(sol::resolve<LuaVec4(const LuaVec4&)>(&LuaVec4::operator/), sol::resolve<LuaVec4(float)>(&LuaVec4::operator/))
		);

		this->_SolState.new_usertype<LuaVec3>("Vec3", sol::constructors<void(LuaVec3), void(), void(float), void(float, float, float)>(),
			"x", &LuaVec3::x,
			"y", &LuaVec3::y,
			"z", &LuaVec3::z,
			"Length", &LuaVec3::Length,
			"Length2", &LuaVec3::Length2,
			"Normalize", &LuaVec3::Normalize,
			"Cross", &LuaVec3::Cross,
			"Reflect", &LuaVec3::Reflect,
			sol::meta_function::addition, sol::overload(sol::resolve<LuaVec3(const LuaVec3&)>(&LuaVec3::operator+), sol::resolve<LuaVec3(float)>(&LuaVec3::operator+)),
			sol::meta_function::subtraction, sol::overload(sol::resolve<LuaVec3(const LuaVec3&)>(&LuaVec3::operator-), sol::resolve<LuaVec3(float)>(&LuaVec3::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<LuaVec3(const LuaVec3&)>(&LuaVec3::operator*), sol::resolve<LuaVec3(float)>(&LuaVec3::operator*)),
			sol::meta_function::division, sol::overload(sol::resolve<LuaVec3(const LuaVec3&)>(&LuaVec3::operator/), sol::resolve<LuaVec3(float)>(&LuaVec3::operator/))
		);

		this->_SolState.new_usertype<LuaVec2>("Vec2", sol::constructors<void(LuaVec2), void(), void(float), void(float, float)>(),
			"x", &LuaVec2::x,
			"y", &LuaVec2::y,
			"Length", &LuaVec2::Length,
			"Length2", &LuaVec2::Length2,
			"Normalize", &LuaVec2::Normalize,
			"Reflect", &LuaVec2::Reflect,
			sol::meta_function::addition, sol::overload(sol::resolve<LuaVec2(const LuaVec2&)>(&LuaVec2::operator+), sol::resolve<LuaVec2(float)>(&LuaVec2::operator+)),
			sol::meta_function::subtraction, sol::overload(sol::resolve<LuaVec2(const LuaVec2&)>(&LuaVec2::operator-), sol::resolve<LuaVec2(float)>(&LuaVec2::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<LuaVec2(const LuaVec2&)>(&LuaVec2::operator*), sol::resolve<LuaVec2(float)>(&LuaVec2::operator*)),
			sol::meta_function::division, sol::overload(sol::resolve<LuaVec2(const LuaVec2&)>(&LuaVec2::operator/), sol::resolve<LuaVec2(float)>(&LuaVec2::operator/))
		);

		this->_SolState.new_usertype<LuaTexture>("Texture", sol::constructors<void(const std::string&)>());

		this->_SolState.new_usertype<LuaMesh>("Mesh", sol::constructors<void(const std::string&)>());

		this->_SolState.new_usertype<LuaShader>("Shader", sol::constructors<void(const std::string&)>());

		this->_SolState.new_usertype<LuaMaterial>("Material", sol::constructors<void(LuaShader)>(),
			"SetInt", &LuaMaterial::SetInt,
			"SetFloat", &LuaMaterial::SetFloat,
			"SetDouble", &LuaMaterial::SetDouble,
			"SetVec2", &LuaMaterial::SetVec2,
			"SetVec3", &LuaMaterial::SetVec3,
			"SetTexture", &LuaMaterial::SetTexture
		);

		//Tables

		this->_SolState.create_named_table("Scene",
			"TimeSinceStart", [ThisScene](sol::table Self) { return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - ThisScene->GetStartTime()).count(); },
			"CreateEntity", [ThisScene](sol::table Self) { return LuaEntity(ThisScene, ThisScene->CreateEntity()); },
			"DeleteEntity", [ThisScene](sol::table Self, LuaEntity& E) { return ThisScene->DestroyEntity(E.Get()); },
			"View", sol::overload(
				[ThisScene](sol::this_state S, sol::table Self, LuaComponentID ComponentID) { return LuaState::LuaComponentView(S, ThisScene, ComponentID); },
				[ThisScene](sol::this_state S, sol::table Self, sol::table ScriptTable) { return LuaState::LuaScriptView(S, ThisScene, ScriptTable); })
		);

		this->_SolState.create_named_table("Input",
			"IsHeld", [ThisInput](sol::table Self, char KeyCode) { return ThisInput->IsHeld(KeyCode); },
			"IsPressed", [ThisInput](sol::table Self, char KeyCode) { return ThisInput->IsPressed(KeyCode); },
			"IsMouseButtonHeld", [ThisInput](sol::table Self, char Button) { return ThisInput->IsMouseButtonHeld(Button); },
			"IsMouseButtonPressed", [ThisInput](sol::table Self, char Button) { return ThisInput->IsMouseButtonPressed(Button); },
			"GetScrollPosition", [ThisInput](sol::table Self) { return ThisInput->GetScrollPosition(); },
			"GetMousePosition", [ThisInput](sol::table Self) { return ThisInput->GetMousePosition(); }
		);

		this->_SolState.create_named_table("Window",
			"SetCursorMode", [ThisWindow](sol::table Self, CursorMode NewCursorMode) { return ThisWindow->SetCursorMode(NewCursorMode); },
			"SetTitle", [ThisWindow](sol::table Self, const std::string& NewTitle) { return ThisWindow->SetTitle(NewTitle); },
			"SetVsync", [ThisWindow](sol::table Self, bool Enabled) { return ThisWindow->SetVsync(Enabled); }
		);

		//Enums

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
}