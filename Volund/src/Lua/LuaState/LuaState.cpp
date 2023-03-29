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
	void LuaState::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (e.Type)
		{
		case EventType::Update:
		{
			static float totalTime = 0.0f;
			totalTime += VOLUND_EVENT_UPDATE_GET_TIMESTEP(e);

			if (totalTime > 0.1f)
			{
				this->m_SolState.collect_garbage();
				totalTime = 0.0f;
			}
		}
		break;
		}
	}

	void LuaState::ScriptFile(const std::string& filepath)
	{
		this->m_SolState.safe_script_file(filepath, [](lua_State*, sol::protected_function_result pfr)
		{		
			sol::error err = pfr;
			VOLUND_WARNING(err.what());

			return pfr;
		});
	}

	void LuaState::LuaPrint(sol::object object)
	{
		VOLUND_INFO(object.as<std::string>().c_str());
	}

	sol::object LuaState::LuaRequire(sol::this_state s, std::string filepath)
	{
		std::string source = Filesystem::LoadFile(filepath);

		sol::state_view state = s;
		return state.require_script(filepath, source);
	}

	sol::table LuaState::LuaComponentView(sol::this_state s, LuaComponentID ComponentID)
	{
		switch (ComponentID)
		{
		case LuaComponentID::Camera:
		{
			return this->GenerateComponentView<Camera>(s);
		}
		break;
		case LuaComponentID::CameraMovement:
		{
			return this->GenerateComponentView<CameraMovement>(s);
		}
		break;
		case LuaComponentID::MeshRenderer:
		{
			return this->GenerateComponentView<MeshRenderer>(s);
		}
		break;
		case LuaComponentID::PointLight:
		{
			return this->GenerateComponentView<PointLight>(s);
		}
		break;
		case LuaComponentID::Script:
		{
			return this->GenerateComponentView<Script>(s);
		}
		break;
		case LuaComponentID::Tag:
		{
			return this->GenerateComponentView<Tag>(s);
		}
		break;
		case LuaComponentID::Transform:
		{
			return this->GenerateComponentView<Transform>(s);
		}
		break;
		case LuaComponentID::SoundSource:
		{
			return this->GenerateComponentView<SoundSource>(s);
		}
		break;
		case LuaComponentID::SoundListener:
		{
			return this->GenerateComponentView<SoundListener>(s);
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

	sol::table LuaState::LuaScriptView(sol::this_state s, sol::table scriptTable)
	{
		sol::state_view stateView = s;

		sol::table output = stateView.create_table_with();

		std::vector<Ref<Script>> view;
		this->m_Scene->View(view);

		for (auto& component : view)
		{
			if (component->Compare(scriptTable))
			{
				output.add(component->Table);
			}
		}

		return output;
	}

	LuaState::LuaState(Ref<Scene> scene, Ref<Input> input, Ref<Window> window)
	{
		VOLUND_PROFILE_FUNCTION();

		window->Reset();

		this->m_Scene = scene;
		this->m_Input = input;
		this->m_Window = window;

		this->m_SolState.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string, sol::lib::utf8, sol::lib::os, sol::lib::table, sol::lib::io, sol::lib::package);

		//Functions

		this->m_SolState["require"] = LuaRequire;
		this->m_SolState["print"] = LuaPrint;

		//Usertypes

		this->m_SolState.new_usertype<LuaEntity>("VOLUND_ENTITY", sol::no_constructor,
			"Padding", &LuaEntity::Padding,
			"Add", &LuaEntity::AddComponent,
			"Delete", &LuaEntity::DeleteComponent,
			"Get", &LuaEntity::GetComponent,
			"GetScript", &LuaEntity::GetScript,
			"HasComponent", &LuaEntity::HasComponent,
			"ComponentAmount", &LuaEntity::ComponentAmount
		);

		this->m_SolState.new_usertype<LuaVec4>("Vec4", sol::constructors<void(LuaVec4), void(), void(float), void(float, float, float, float)>(),
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

		this->m_SolState.new_usertype<LuaVec3>("Vec3", sol::constructors<void(LuaVec3), void(), void(float), void(float, float, float)>(),
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

		this->m_SolState.new_usertype<LuaVec2>("Vec2", sol::constructors<void(LuaVec2), void(), void(float), void(float, float)>(),
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

		this->m_SolState.new_usertype<LuaTexture>("Texture", sol::constructors<void(const std::string&)>(),
			"Padding", &LuaTexture::Padding);

		this->m_SolState.new_usertype<LuaFramebuffer>("Framebuffer", sol::constructors<void(const LuaVec2&)>(),
			"Padding", &LuaFramebuffer::Padding,
			"Resize", &LuaFramebuffer::Resize,
			"GetSize", &LuaFramebuffer::GetSize);

		this->m_SolState.new_usertype<LuaMesh>("Mesh", sol::constructors<void(const std::string&)>(),
			"Padding", &LuaMesh::Padding);

		this->m_SolState.new_usertype<LuaShader>("Shader", sol::constructors<void(const std::string&)>(),
			"Padding", &LuaShader::Padding);

		this->m_SolState.new_usertype<LuaSound>("Sound", sol::constructors<void(const std::string&)>(),
			"Padding", &LuaSound::Padding);

		this->m_SolState.new_usertype<LuaMaterial>("Material", sol::constructors<void(LuaShader)>(),
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

		this->m_SolState.create_named_table("Scene",
			"GetTargetBuffer", std::function([this](sol::table self) { return LuaFramebuffer(this->m_Scene->GetTargetBuffer()); }),
			"TimeSinceStart", std::function([this](sol::table self) { return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - this->m_Scene->GetStartTime()).count(); }),
			"CreateEntity", std::function([this](sol::table self) { return LuaEntity(this->m_Scene, this->m_Scene->CreateEntity()); }),
			"DeleteEntity", std::function([this](sol::table self, LuaEntity& e) { return this->m_Scene->DestroyEntity(e.Get()); }),
			"View", sol::overload(
				std::function([this](sol::this_state s, sol::table self, LuaComponentID ComponentID) { return this->LuaComponentView(s, ComponentID); }),
				std::function([this](sol::this_state s, sol::table self, sol::table scriptTable) { return this->LuaScriptView(s, scriptTable); }))
		);

		this->m_SolState.create_named_table("Input",
			"IsHeld", std::function([this](sol::table self, char keyCode) { return this->m_Input->IsHeld(keyCode); }),
			"IsPressed", std::function([this](sol::table self, char keyCode) { return this->m_Input->IsPressed(keyCode); }),
			"IsMouseButtonHeld", std::function([this](sol::table self, char button) { return this->m_Input->IsMouseButtonHeld(button); }),
			"IsMouseButtonPressed", std::function([this](sol::table self, char button) { return this->m_Input->IsMouseButtonPressed(button); }),
			"GetScrollPosition", std::function([this](sol::table self) { return this->m_Input->GetScrollPosition(); }),
			"GetMousePosition", std::function([this](sol::table self) { return this->m_Input->GetMousePosition(); })
		);

		this->m_SolState.create_named_table("Window",
			"SetCursorMode", std::function([this](sol::table self, CursorMode newCursorMode) { return this->m_Window->SetCursorMode(newCursorMode); }),
			"SetTitle", std::function([this](sol::table self, const std::string& newTitle) { return this->m_Window->SetTitle(newTitle); })
		);

		//Enums

		this->m_SolState.new_enum("Component",
			"CAMERA", LuaComponentID::Camera,
			"CAMERA_MOVEMENT", LuaComponentID::CameraMovement,
			"MESH_RENDERER", LuaComponentID::MeshRenderer,
			"POINT_LIGHT", LuaComponentID::PointLight,
			"SCRIPT", LuaComponentID::Script,
			"TAG", LuaComponentID::Tag,
			"TRANSFORM", LuaComponentID::Transform,
			"SOUND_SOURCE", LuaComponentID::SoundSource,
			"SOUND_LISTENER", LuaComponentID::SoundListener
		);

		this->m_SolState.new_enum("CursorMode",
			"NORMAL", CursorMode::Normal,
			"HIDDEN", CursorMode::Hidden,
			"DISABLED", CursorMode::Disabled
		);
	}

	LuaState::~LuaState()
	{
		this->m_SolState.collect_garbage();
	}
}