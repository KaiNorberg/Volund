#include "PCH/PCH.h"
#include "LuaDeserializer.h"

#include <sol/sol.hpp>

#include "Lua/LuaUtils/LuaUtils.h"

#define VOLUND_DESERIALIZER_TABLE "Data"

namespace Volund
{
	void LuaDeserializerPrint(sol::object object)
	{
		VOLUND_INFO(object.as<std::string>().c_str());
	}

	void LuaDeserializerRequire(sol::this_state s, std::string filepath)
	{
		VOLUND_WARNING("Data files are not allowed to require other files!");
	}
	
	////////////////////////////////////////////////////////////////////

	uint64_t LuaDeserializer::Size()
	{
		return this->GetTable().size();
	}

	bool LuaDeserializer::Valid()
	{
		return this->m_Valid;
	}

	sol::object LuaDeserializer::operator[](uint64_t i)
	{
		return this->GetTable()[i];
	}

	sol::object LuaDeserializer::operator[](const std::string& key)
	{
		return this->GetTable()[key];
	}

	sol::table::iterator LuaDeserializer::begin()
	{
		return this->GetTable().begin();
	}

	sol::table::iterator LuaDeserializer::end()
	{
		return this->GetTable().end();
	}

    sol::table LuaDeserializer::GetTable()
    {
        return ((sol::object)(*this->m_SolState)[VOLUND_DESERIALIZER_TABLE]).as<sol::table>();
    }

    LuaDeserializer::LuaDeserializer(const std::string& filepath)
	{
		VOLUND_PROFILE_FUNCTION();

		this->m_SolState = std::make_shared<sol::state>();
		//this->m_SolState->open_libraries(sol::lib::base, sol::lib::table);

		
		//Global Functions

		(*this->m_SolState)["require"] = LuaDeserializerRequire;
		(*this->m_SolState)["print"] = LuaDeserializerPrint;

		//Global UserTypes

		this->m_SolState->new_usertype<Vec4>("Vec4", sol::constructors<void(float, float, float, float)>());
		this->m_SolState->new_usertype<Vec3>("Vec3", sol::constructors<void(float, float, float)>());
		this->m_SolState->new_usertype<Vec2>("Vec2", sol::constructors<void(float, float)>());

		if (!filepath.empty())
		{
			sol::object object = LuaUtils::ScriptFile(this->m_SolState, filepath);

			if (object.is<sol::table>())
			{
				this->m_Valid = true;

				(*this->m_SolState)[VOLUND_DESERIALIZER_TABLE] = object;
			}
			else
			{
				VOLUND_WARNING("Lua data file is not valid %s!", filepath.c_str());
				this->m_Valid = false;
			}
		}
		else
		{
			this->m_Valid = true;

			this->m_SolState->create_named_table(VOLUND_DESERIALIZER_TABLE);
		}
	}

	LuaDeserializer::~LuaDeserializer()
	{

	}
}