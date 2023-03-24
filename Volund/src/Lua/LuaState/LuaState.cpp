#include "PCH/PCH.h"
#include "LuaState.h"

#include "Scene/Component/Components.h"

#include "Lua/LuaEntity/LuaEntity.h"
#include "Lua/LuaVec/LuaVec.h"
#include "Lua/LuaMaterial/LuaMaterial.h"
#include "Lua/LuaMesh/LuaMesh.h"
#include "Lua/LuaShader/LuaShader.h"
#include "Lua/LuaTexture/LuaTexture.h"
#include "Lua/LuaSound/LuaSound.h"
#include "Lua/LuaFramebuffer/LuaFramebuffer.h"

#include "Filesystem/Filesystem.h"

#include "Scene/Scene.h"
#include "Scene/Component/Components.h"

#include "Renderer/Material/Material.h"
#include "Renderer/Mesh/Mesh.h"

#include "Window/Window.h"

namespace Volund
{
	void LuaState::Procedure(const Event& E)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (E.Type)
		{
		case EventType::UPDATE:
		{
			static float TotalTime = 0.0f;
			TotalTime += VOLUND_EVENT_UPDATE_GET_TIMESTEP(E);

			if (TotalTime > 0.1f)
			{
				this->_SolState.collect_garbage();
				TotalTime = 0.0f;
			}
		}
		break;
		}
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

	sol::table LuaState::LuaComponentView(sol::this_state S, LuaComponentID ComponentID)
	{
		switch (ComponentID)
		{
		case LuaComponentID::CAMERA:
		{
			return this->GenerateComponentView<Camera>(S);
		}
		break;
		case LuaComponentID::CAMERA_MOVEMENT:
		{
			return this->GenerateComponentView<CameraMovement>(S);
		}
		break;
		case LuaComponentID::MESH_RENDERER:
		{
			return this->GenerateComponentView<MeshRenderer>(S);
		}
		break;
		case LuaComponentID::POINT_LIGHT:
		{
			return this->GenerateComponentView<PointLight>(S);
		}
		break;
		case LuaComponentID::SCRIPT:
		{
			return this->GenerateComponentView<Script>(S);
		}
		break;
		case LuaComponentID::TAG:
		{
			return this->GenerateComponentView<Tag>(S);
		}
		break;
		case LuaComponentID::TRANSFORM:
		{
			return this->GenerateComponentView<Transform>(S);
		}
		break;
		case LuaComponentID::SOUND_SOURCE:
		{
			return this->GenerateComponentView<SoundSource>(S);
		}
		break;
		case LuaComponentID::SOUND_LISTENER:
		{
			return this->GenerateComponentView<SoundListener>(S);
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

	sol::table LuaState::LuaScriptView(sol::this_state S, sol::table ScriptTable)
	{
		sol::state_view StateView = S;

		sol::table Output = StateView.create_table_with();

		std::vector<Ref<Script>> View;
		this->_Scene->View(View);

		for (auto& Component : View)
		{
			if (Component->Compare(ScriptTable))
			{
				Output.add(Component->Table);
			}
		}

		return Output;
	}

	LuaState::LuaState(Ref<Scene> ThisScene, Ref<Input> ThisInput, Ref<Window> ThisWindow)
	{
		VOLUND_PROFILE_FUNCTION();

		ThisWindow->Reset();

		this->_Scene = ThisScene;
		this->_Input = ThisInput;
		this->_Window = ThisWindow;

		this->_SolState.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string, sol::lib::utf8, sol::lib::os, sol::lib::table, sol::lib::io, sol::lib::package);

		//Functions

		this->_SolState["require"] = LuaRequire;
		this->_SolState["print"] = LuaPrint;

		//Usertypes

		this->_SolState.new_usertype<LuaEntity>("VOLUND_ENTITY", sol::no_constructor,
			"Padding", &LuaEntity::Padding,
			"Add", &LuaEntity::AddComponent,
			"Delete", &LuaEntity::DeleteComponent,
			"Get", &LuaEntity::GetComponent,
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

		this->_SolState.new_usertype<LuaTexture>("Texture", sol::constructors<void(const std::string&)>(),
			"Padding", &LuaTexture::Padding);

		this->_SolState.new_usertype<LuaFramebuffer>("Framebuffer", sol::constructors<void(const LuaVec2&)>(),
			"Padding", &LuaFramebuffer::Padding,
			"Resize", &LuaFramebuffer::Resize,
			"GetSize", &LuaFramebuffer::GetSize);

		this->_SolState.new_usertype<LuaMesh>("Mesh", sol::constructors<void(const std::string&)>(),
			"Padding", &LuaMesh::Padding);

		this->_SolState.new_usertype<LuaShader>("Shader", sol::constructors<void(const std::string&)>(),
			"Padding", &LuaShader::Padding);

		this->_SolState.new_usertype<LuaSound>("Sound", sol::constructors<void(const std::string&)>(),
			"Padding", &LuaSound::Padding);

		this->_SolState.new_usertype<LuaMaterial>("Material", sol::constructors<void(LuaShader)>(),
			"Padding", &LuaMaterial::Padding,
			"SetInt", &LuaMaterial::SetInt,
			"SetFloat", &LuaMaterial::SetFloat,
			"SetDouble", &LuaMaterial::SetDouble,
			"SetVec2", &LuaMaterial::SetVec2,
			"SetVec3", &LuaMaterial::SetVec3,
			"SetTexture", &LuaMaterial::SetTexture,
			"SetFramebuffer", &LuaMaterial::SetFramebuffer
		);

		//Tables

		this->_SolState.create_named_table("Scene",
			"GetTargetBuffer", std::function([this](sol::table Self) { return LuaFramebuffer(this->_Scene->GetTargetBuffer()); }),
			"TimeSinceStart", std::function([this](sol::table Self) { return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - this->_Scene->GetStartTime()).count(); }),
			"CreateEntity", std::function([this](sol::table Self) { return LuaEntity(this->_Scene, this->_Scene->CreateEntity()); }),
			"DeleteEntity", std::function([this](sol::table Self, LuaEntity& E) { return this->_Scene->DestroyEntity(E.Get()); }),
			"View", sol::overload(
				std::function([this](sol::this_state S, sol::table Self, LuaComponentID ComponentID) { return this->LuaComponentView(S, ComponentID); }),
				std::function([this](sol::this_state S, sol::table Self, sol::table ScriptTable) { return this->LuaScriptView(S, ScriptTable); }))
		);

		this->_SolState.create_named_table("Input",
			"IsHeld", std::function([this](sol::table Self, char KeyCode) { return this->_Input->IsHeld(KeyCode); }),
			"IsPressed", std::function([this](sol::table Self, char KeyCode) { return this->_Input->IsPressed(KeyCode); }),
			"IsMouseButtonHeld", std::function([this](sol::table Self, char Button) { return this->_Input->IsMouseButtonHeld(Button); }),
			"IsMouseButtonPressed", std::function([this](sol::table Self, char Button) { return this->_Input->IsMouseButtonPressed(Button); }),
			"GetScrollPosition", std::function([this](sol::table Self) { return this->_Input->GetScrollPosition(); }),
			"GetMousePosition", std::function([this](sol::table Self) { return this->_Input->GetMousePosition(); })
		);

		this->_SolState.create_named_table("Window",
			"SetCursorMode", std::function([this](sol::table Self, CursorMode NewCursorMode) { return this->_Window->SetCursorMode(NewCursorMode); }),
			"SetTitle", std::function([this](sol::table Self, const std::string& NewTitle) { return this->_Window->SetTitle(NewTitle); })
		);

		//Enums

		this->_SolState.new_enum("Component",
			"CAMERA", LuaComponentID::CAMERA,
			"CAMERA_MOVEMENT", LuaComponentID::CAMERA_MOVEMENT,
			"MESH_RENDERER", LuaComponentID::MESH_RENDERER,
			"POINT_LIGHT", LuaComponentID::POINT_LIGHT,
			"SCRIPT", LuaComponentID::SCRIPT,
			"TAG", LuaComponentID::TAG,
			"TRANSFORM", LuaComponentID::TRANSFORM,
			"SOUND_SOURCE", LuaComponentID::SOUND_SOURCE,
			"SOUND_LISTENER", LuaComponentID::SOUND_LISTENER
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
		this->_SolState.collect_garbage();
	}
}