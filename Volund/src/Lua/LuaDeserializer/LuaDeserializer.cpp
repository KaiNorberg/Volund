#include "PCH/PCH.h"
#include "LuaDeserializer.h"

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
		return this->GetData().size();
	}

	bool LuaDeserializer::Valid()
	{
		return this->m_Valid;
	}

	sol::object LuaDeserializer::operator[](uint64_t i)
	{
		return this->GetData()[i];
	}

	sol::object LuaDeserializer::operator[](const std::string& key)
	{
		return this->GetData()[key];
	}

	sol::table::iterator LuaDeserializer::begin()
	{
		return this->GetData().begin();
	}

	sol::table::iterator LuaDeserializer::end()
	{
		return this->GetData().end();
	}

    sol::table LuaDeserializer::GetData()
    {
		return this->m_Table[VOLUND_SERIAL_DATA];
    }

    LuaDeserializer::LuaDeserializer(const std::string& filepath, const std::string& fileType)
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
			sol::object returnVal = LuaUtils::ScriptFile(this->m_SolState, filepath);

			if (returnVal.is<sol::table>())
			{
				sol::table table = returnVal;

				std::string recivedFileType = table[VOLUND_SERIAL_FILE_TYPE];

				if (recivedFileType == fileType)
				{
					this->m_Valid = true;

					this->m_Table = returnVal;
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

			this->m_Table = this->m_SolState->create_table();
			this->m_Table[VOLUND_SERIAL_FILE_TYPE] = fileType;
			this->m_Table[VOLUND_SERIAL_DATA] = this->m_SolState->create_table();
		}
	}

	LuaDeserializer::~LuaDeserializer()
	{
		this->m_Table.reset();
	}
}