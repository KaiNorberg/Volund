#pragma once

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

		sol::table GetTable();

		LuaDeserializer(const std::string& filepath = "");

		virtual ~LuaDeserializer();

	private:

		bool m_Valid = false;

		Ref<sol::state> m_SolState;
	};
}

