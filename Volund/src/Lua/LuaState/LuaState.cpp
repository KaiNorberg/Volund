#include "PCH/PCH.h"
#include "LuaState.h"

#include "Filesystem/Filesystem.h"

#include "Lua/LuaVec/LuaVec.h"
#include "Lua/LuaComponent/LuaComponentID.h"

#include <sol/sol.hpp>

namespace Volund
{
	void LuaPrint(sol::object object)
	{
		VOLUND_INFO(object.as<std::string>().c_str());
	}

	sol::object LuaRequire(sol::this_state s, std::string filepath)
	{
		auto source = Filesystem::Load(filepath);

		sol::state_view state = s;
		return state.require_script(filepath, source);
	}
	
	////////////////////////////////////////////////////////////////////

	/*void LuaState::Procedure(const Event& e)
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
	}*/

	void LuaState::ScriptFile(const std::string& filepath)
	{
		try
		{
			this->m_SolState->script_file(filepath, [](lua_State*, sol::protected_function_result pfr)
			{		
				sol::error err = pfr;
				VOLUND_WARNING(err.what());

				return pfr;
			});
		}
		catch(const sol::error& e)
		{
			VOLUND_WARNING(e.what());
		}
	}

	LuaState::LuaState()
	{
		VOLUND_PROFILE_FUNCTION();
		
		VOLUND_INFO("Creating lua state...");

		this->m_SolState = std::make_shared<sol::state>();

		this->m_SolState->open_libraries(sol::lib::base, sol::lib::math, sol::lib::string, sol::lib::utf8, sol::lib::os, sol::lib::table, sol::lib::io, sol::lib::package);

		//Functions

		(*this->m_SolState)["require"] = LuaRequire;
		(*this->m_SolState)["print"] = LuaPrint;

		//Usertypes

		this->m_SolState->new_usertype<LuaVec4>("Vec4", sol::constructors<void(LuaVec4), void(), void(float), void(float, float, float, float)>(),
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

		this->m_SolState->new_usertype<LuaVec3>("Vec3", sol::constructors<void(LuaVec3), void(), void(float), void(float, float, float)>(),
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

		this->m_SolState->new_usertype<LuaVec2>("Vec2", sol::constructors<void(LuaVec2), void(), void(float), void(float, float)>(),
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

		//Tables
			
		//Enums

		this->m_SolState->new_enum("Component",
			"Camera", LuaComponentID::Camera,
			"CameraMovement", LuaComponentID::CameraMovement,
			"MeshRenderer", LuaComponentID::MeshRenderer,
			"PointLight", LuaComponentID::PointLight,
			//"SCRIPT", LuaComponentID::Script,
			"Tag", LuaComponentID::Tag,
			"Transform", LuaComponentID::Transform,
			"SoundSource", LuaComponentID::SoundSource,
			"SoundListener", LuaComponentID::SoundListener
		);

		/*this->m_SolState.new_enum("CursorMode",
			"NORMAL", CursorMode::Normal,
			"HIDDEN", CursorMode::Hidden,
			"DISABLED", CursorMode::Disabled
		);*/
	}

	LuaState::~LuaState()
	{

	}
}