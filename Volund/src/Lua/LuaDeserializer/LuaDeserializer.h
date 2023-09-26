#pragma once

#include "Lua/LuaUtils/LuaUtils.h"

namespace Volund 
{
	class LuaDeserializer
	{
	public:

		uint64_t Size();

		bool Valid();

		sol::object operator[](uint64_t i);

		sol::object operator[](const std::string& key);

		sol::table::iterator begin();

		sol::table::iterator end();

		LuaDeserializer(const std::string& filepath, const std::string& fileType);

		virtual ~LuaDeserializer();

	private:

		sol::table GetData();

		bool m_Valid = false;

		sol::table m_Table;

		Ref<sol::state> m_SolState;
	};
}

