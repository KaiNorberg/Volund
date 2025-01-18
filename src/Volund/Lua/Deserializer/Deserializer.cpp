#include "Deserializer.h"

#include "Lua/LuaUtils/LuaUtils.h"
#include "Lua/LuaTypes.h"
#include "Instrumentor.h"
#include "AssetManager/AssetManager.h"
#include "Lua/Serializer/Serializer.h"

#include <sol/sol.hpp>

namespace Volund
{
	void DeserializerPrint(sol::object object)
	{
		VOLUND_INFO(object.as<std::string>().c_str());
	}

	void DeserializerRequire(sol::this_state s, std::string filepath)
	{
		VOLUND_WARNING("Data files are not allowed to require other files!");
	}

	////////////////////////////////////////////////////////////////////

	bool Deserializer::Valid()
	{
		return this->m_Valid;
	}

	PrimitiveSerialObject& Deserializer::operator[](std::string const& key)
	{
		return this->m_Table[key];
	}

	const SerialTable::const_iterator Deserializer::begin() const
	{
		return this->m_Table.begin();
	}

	const SerialTable::const_iterator Deserializer::end() const
	{
		return this->m_Table.end();
	}

	SerialTable::iterator Deserializer::begin()
	{
		return this->m_Table.begin();
	}

	SerialTable::iterator Deserializer::end()
	{
		return this->m_Table.end();
	}

    Deserializer::Deserializer(std::string const& filepath, std::string const& fileType)
	{
		VOLUND_PROFILE_FUNCTION();

		auto luaState = std::make_shared<sol::state>();
		//this->m_SolState->open_libraries(sol::lib::base, sol::lib::table);

		//Global Functions

		(*luaState)["require"] = DeserializerRequire;
		(*luaState)["print"] = DeserializerPrint;

		//Global UserTypes

		luaState->new_usertype<Vec4>("Vec4", sol::constructors<void(float, float, float, float)>());
		luaState->new_usertype<Vec3>("Vec3", sol::constructors<void(float, float, float)>());
		luaState->new_usertype<LuaVec2>("Vec2", sol::constructors<void(float, float)>());

		if (!filepath.empty())
		{
			sol::object returnVal = LuaUtils::ScriptFile(luaState, filepath);

			if (returnVal.is<sol::table>())
			{
				sol::table table = returnVal;

				std::string recivedFileType = table[VOLUND_SERIAL_FILE_TYPE];

				if (recivedFileType == fileType)
				{
					this->m_Valid = true;

					this->m_Table = LuaUtils::DeserializeTable(table[VOLUND_SERIAL_DATA]);
				}
				else
				{
					VOLUND_WARNING("Lua file type mismatch %s, expected %s recived %s!", filepath.c_str(), fileType.c_str(), recivedFileType.c_str());
				}
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

			//TODO: Implement this
		}
	}

	Deserializer::~Deserializer()
	{
	}
}
