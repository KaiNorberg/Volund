#include "PCH/PCH.h"
#include "LuaContext.h"

extern "C"
{
#include "lua/include/lua.h"
#include "lua/include/lauxlib.h"
#include "lua/include/lualib.h"
}

#include <cstdarg>

namespace Volund
{
	bool LuaContext::DoString(const std::string& String)
	{
		return this->LuaErrorCheck(luaL_dostring(this->_State, String.c_str()));
	}

	bool LuaContext::DoFile(const std::string& Filepath)
	{
		return this->LuaErrorCheck(luaL_dofile(this->_State, Filepath.c_str()));
	}

	void LuaContext::PushInt(int64_t Int)
	{
		lua_pushinteger(this->_State, Int);
	}

	void LuaContext::PushString(const char* String)
	{
		lua_pushstring(this->_State, String);
	}

	void LuaContext::PushNumber(float Float)
	{
		lua_pushnumber(this->_State, Float);
	}

	void LuaContext::CallFunction(const std::string& Name)
	{
		lua_getglobal(this->_State, Name.c_str());
		if (lua_isfunction(this->_State, -1))
		{
			if (LuaErrorCheck(lua_pcall(this->_State, 0, 0, 0)))
			{

			}
		}
	}

	LuaValue LuaContext::GetGlobal(const std::string& Name)
	{
		lua_getglobal(this->_State, Name.c_str());
		return LuaValue(-1, this->_State);
	}

	void LuaContext::AddLibrary(const LuaLibrary& Lib)
	{
		for (auto& Entry : Lib)
		{
			lua_register(this->_State, Entry.first.c_str(), Entry.second);
		}
	}

	LuaContext::LuaContext()
	{
		this->_State = luaL_newstate();
		luaL_openlibs(this->_State);
	}

	LuaContext::LuaContext(lua_State* State)
	{
		this->_State = State;
	}

	LuaContext::~LuaContext()
	{
		lua_close(this->_State);
	}

	bool LuaContext::LuaErrorCheck(int R)
	{
		if (R == LUA_OK)
		{
			return true;
		}
		else
		{
			std::string Error = lua_tostring(this->_State, -1);
			VOLUND_WARNING("Lua Error: %s", Error.c_str());
		
			return false;
		}
	}
}