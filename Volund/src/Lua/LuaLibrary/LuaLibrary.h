#pragma once

struct lua_State;

namespace Volund
{
	using LibEntry = std::pair<std::string, int(*)(lua_State*)>;

	class LuaLibrary
	{
	public:

		std::vector<LibEntry>::const_iterator begin() const;
		std::vector<LibEntry>::const_iterator end() const;

		LuaLibrary(std::initializer_list<LibEntry> List);

	private:

		std::vector<LibEntry> _Functions;
	};
}