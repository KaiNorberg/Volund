#pragma once

#include "Lua/LuaValue/LuaValue.h"

#include "Lua/LuaLibrary/LuaLibrary.h"

struct lua_State;

namespace Volund
{
	class LuaContext
	{
	public:

		bool DoString(const std::string& String);

		bool DoFile(const std::string& Filepath);

		void PushInt(int64_t Int);

		void PushString(const char* String);

		void PushNumber(float Float);

		void CallFunction(const std::string& Name);

		LuaValue GetGlobal(const std::string& Name);

		void AddLibrary(const LuaLibrary& Lib);

		LuaContext();

		LuaContext(lua_State* State);

		~LuaContext();

	private:

		bool LuaErrorCheck(int R);

		lua_State* _State;
	};
}

