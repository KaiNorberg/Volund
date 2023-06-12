#pragma once

namespace Volund 
{
	class LuaData
	{
	public:

		uint64_t Size();

		bool Valid();

		sol::object operator[](uint64_t i);

		sol::object operator[](const std::string& key);

		sol::table::iterator begin();

		sol::table::iterator end();

		LuaData(const std::string& filepath = "");

		virtual ~LuaData();

	private:

		bool m_Valid = false;

		sol::table m_Table;

		Ref<sol::state> m_SolState;
	};
}

