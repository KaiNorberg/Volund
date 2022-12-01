#include "PCH/PCH.h"
#include "LuaValue.h"

extern "C"
{
#include "lua/include/lua.h"
#include "lua/include/lauxlib.h"
#include "lua/include/lualib.h"
}

namespace Volund
{
	bool LuaValue::IsInt()
	{
		return lua_isinteger(this->_State, this->_Index);
	}

	bool LuaValue::IsString()
	{
		return lua_isstring(this->_State, this->_Index);
	}

	bool LuaValue::IsNumber()
	{
		return lua_isnumber(this->_State, this->_Index);
	}

	bool LuaValue::IsTable()
	{
		return lua_istable(this->_State, this->_Index);
	}

	int64_t LuaValue::Int()
	{
		return lua_tointeger(this->_State, this->_Index);
	}

	std::string LuaValue::String()
	{
		return lua_tostring(this->_State, this->_Index);
	}

	float LuaValue::Number()
	{
		return lua_tonumber(this->_State, this->_Index);
	}

	int64_t LuaValue::Int(const std::string& Key)
	{
		int R = NULL_LUA;

		if (IsTable())
		{
			lua_pushstring(this->_State, Key.c_str());
			lua_gettable(this->_State, -2);

			if (lua_isinteger(this->_State, -1))
			{
				R = lua_tointeger(this->_State, -1);
			}
			lua_pop(this->_State, 1);
		}

		return R;
	}

	std::string LuaValue::String(const std::string& Key)
	{
		std::string R = "";

		if (IsTable())
		{
			lua_pushstring(this->_State, Key.c_str());
			lua_gettable(this->_State, -2);

			if (lua_isstring(this->_State, -1))
			{
				R = lua_tostring(this->_State, -1);
			}
			lua_pop(this->_State, 1);
		}

		return R;
	}

	float LuaValue::Number(const std::string& Key)
	{
		float R = NULL_LUA;

		if (IsTable())
		{
			lua_pushstring(this->_State, Key.c_str());
			lua_gettable(this->_State, -2);

			if (lua_isnumber(this->_State, -1))
			{
				R = lua_tonumber(this->_State, -1);
			}
			lua_pop(this->_State, 1);
		}

		return R;
	}

	LuaValue* LuaValue::Table(const std::string& Key)
	{
		if (IsTable())
		{
			lua_pushstring(this->_State, Key.c_str());
			lua_gettable(this->_State, -2);

			return new LuaValue(-1, this->_State, true);
		}

		return new LuaValue(0, nullptr);
	}

	int64_t LuaValue::Int(const uint64_t Index)
	{
		int R = NULL_LUA;

		if (IsTable())
		{
			lua_pushinteger(this->_State, Index);
			lua_gettable(this->_State, -2);
			
			if (lua_isinteger(this->_State, -1))
			{
				R = lua_tointeger(this->_State, -1);
			}
			lua_pop(this->_State, 1);
		}

		return R;
	}

	std::string LuaValue::String(const uint64_t Index)
	{
		std::string R = "";

		if (IsTable())
		{
			lua_pushinteger(this->_State, Index);
			lua_gettable(this->_State, -2);

			if (lua_isstring(this->_State, -1))
			{
				R = lua_tostring(this->_State, -1);
			}
			lua_pop(this->_State, 1);
		}

		return R;
	}

	float LuaValue::Number(const uint64_t Index)
	{
		float R = NULL_LUA;

		if (IsTable())
		{
			lua_pushinteger(this->_State, Index);
			lua_gettable(this->_State, -2);

			if (lua_isnumber(this->_State, -1))
			{
				R = lua_tonumber(this->_State, -1);
			}
			lua_pop(this->_State, 1);
		}

		return R;
	}

	LuaValue* LuaValue::Table(const uint64_t Index)
	{
		if (IsTable())
		{
			lua_pushinteger(this->_State, Index);
			lua_gettable(this->_State, -2);

			return new LuaValue(-1, this->_State, true);
		}

		return new LuaValue(0, nullptr);
	}

	LuaValue::operator int64_t()
	{
		return this->Int();
	}

	LuaValue::operator std::string()
	{
		return this->String();
	}

	LuaValue::operator float()
	{
		return this->Number();
	}

	uint32_t LuaValue::Size()
	{
		if (this->IsTable())
		{
			return lua_rawlen(this->_State, this->_Index);
		}
		else
		{
			return 1;
		}
	}

	LuaValue::LuaValue(const int64_t Index, lua_State* State, bool ShouldPop)
	{
		this->_Index = Index;
		this->_State = State;
		this->_ShouldPop = ShouldPop;
	}

	LuaValue::~LuaValue()
	{
		if (this->_ShouldPop)
		{
			lua_pop(this->_State, 1);
		}
	}
}
