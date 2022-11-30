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
		return lua_isinteger(this->_State, this->GetIndex());
	}

	bool LuaValue::IsString()
	{
		return lua_isstring(this->_State, this->GetIndex());
	}

	bool LuaValue::IsNumber()
	{
		return lua_isnumber(this->_State, this->GetIndex());
	}

	bool LuaValue::IsTable()
	{
		return lua_istable(this->_State, this->GetIndex());
	}

	int64_t LuaValue::Int()
	{
		return lua_tointeger(this->_State, this->GetIndex());
	}

	std::string LuaValue::String()
	{
		return lua_tostring(this->_State, this->GetIndex());
	}

	float LuaValue::Number()
	{
		return lua_tonumber(this->_State, this->GetIndex());
	}

	int64_t LuaValue::Int(const std::string& Key)
	{
		if (IsTable())
		{
			lua_pushstring(this->_State, Key.c_str());
			lua_gettable(this->_State, -2);

			if (lua_isinteger(this->_State, -1))
			{
				auto R = lua_tointeger(this->_State, -1);
				lua_pop(this->_State, 1);
				return R;
			}
		}

		return NULL_LUA;
	}

	std::string LuaValue::String(const std::string& Key)
	{
		if (IsTable())
		{
			lua_pushstring(this->_State, Key.c_str());
			lua_gettable(this->_State, -2);

			if (lua_isstring(this->_State, -1))
			{
				auto R = lua_tostring(this->_State, -1);
				lua_pop(this->_State, 1);
				return R;
			}
		}

		return "";
	}

	float LuaValue::Number(const std::string& Key)
	{
		if (IsTable())
		{
			lua_pushstring(this->_State, Key.c_str());
			lua_gettable(this->_State, -2);

			if (lua_isnumber(this->_State, -1))
			{
				auto R = lua_tonumber(this->_State, -1);
				lua_pop(this->_State, 1);
				return R;		
			}
		}

		return NULL_LUA;
	}

	Vec3 LuaValue::Vector3(const std::string& Key)
	{
		if (IsTable())
		{
			lua_pushstring(this->_State, Key.c_str());
			lua_gettable(this->_State, -2);

			if (lua_istable(this->_State, -1))
			{
				lua_pushinteger(this->_State, 1);
				lua_gettable(this->_State, -2);
				float X = NULL_LUA;
				if (lua_isnumber(this->_State, -1))
				{
					X = lua_tonumber(this->_State, -1);
				}
				lua_pop(this->_State, 1);

				lua_pushinteger(this->_State, 2);
				lua_gettable(this->_State, -2);
				float Y = NULL_LUA;
				if (lua_isnumber(this->_State, -1))
				{
					Y = lua_tonumber(this->_State, -1);
				}
				lua_pop(this->_State, 1);

				lua_pushinteger(this->_State, 3);
				lua_gettable(this->_State, -2);
				float Z = NULL_LUA;
				if (lua_isnumber(this->_State, -1))
				{
					Z = lua_tonumber(this->_State, -1);
				}
				lua_pop(this->_State, 1);

				lua_pop(this->_State, 1);

				return Vec3(X, Y, Z);
			}
		}

		return Vec3(NULL_LUA, NULL_LUA, NULL_LUA);
	}

	int64_t LuaValue::Int(const uint64_t Index)
	{
		if (IsTable())
		{
			lua_pushinteger(this->_State, Index);
			lua_gettable(this->_State, -2);
			
			if (lua_isinteger(this->_State, -1))
			{
				auto R = lua_tointeger(this->_State, -1);
				lua_pop(this->_State, 1);
				return R;
			}
		}

		return NULL_LUA;
	}

	std::string LuaValue::String(const uint64_t Index)
	{
		if (IsTable())
		{
			lua_pushinteger(this->_State, Index);
			lua_gettable(this->_State, -2);

			if (lua_isstring(this->_State, -1))
			{
				auto R = lua_tostring(this->_State, -1);
				lua_pop(this->_State, 1);
				return R;
			}
		}

		return "";
	}

	float LuaValue::Number(const uint64_t Index)
	{
		if (IsTable())
		{
			lua_pushinteger(this->_State, Index);
			lua_gettable(this->_State, -2);

			if (lua_isnumber(this->_State, -1))
			{
				auto R = lua_tonumber(this->_State, -1);
				lua_pop(this->_State, 1);
				return R;
			}
		}

		return NULL_LUA;
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

	LuaValue::LuaValue(const uint64_t Index, lua_State* State)
	{
		this->_Index = Index;
		this->_State = State;
	}

	LuaValue::LuaValue(const std::string& Name, lua_State* State)
	{
		this->_Name = Name;
		this->_State = State;
	}

	uint64_t LuaValue::GetIndex()
	{
		if (this->_Index == 0)
		{
			lua_getglobal(this->_State, this->_Name.c_str());
			return -1;
		}
		else
		{
			return this->_Index;
		}
	}
}
