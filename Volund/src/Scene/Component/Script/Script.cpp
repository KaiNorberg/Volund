#include "PCH/PCH.h"
#include "Script.h"

#include "Lua/Lua.h"

#include "Filesystem/Filesystem.h"

namespace Volund
{
	void Script::OnCreate()
	{
		if (this->_LuaOnCreate != sol::lua_nil)
		{
			try
			{
				this->_LuaOnCreate.call<void>(Lua::LuaEntity(this->GetEntity()));
			}
			catch (sol::error E)
			{
				VOLUND_WARNING(E.what());
			}
		}
	}

	void Script::OnUpdate(TimeStep TS)
	{	
		if (this->_LuaOnUpdate != sol::lua_nil)
		{
			try
			{
				this->_LuaOnUpdate.call<void>(Lua::LuaEntity(this->GetEntity()), TS.GetSeconds());
			}
			catch (sol::error E)
			{
				VOLUND_WARNING(E.what());
			}
		}
	}

	void Script::OnDelete()
	{
		if (this->_LuaOnDelete != sol::lua_nil)
		{
			try
			{
				this->_LuaOnDelete.call<void>(Lua::LuaEntity(this->GetEntity()));
			}
			catch (sol::error E)
			{
				VOLUND_WARNING(E.what());
			}
		}
	}

	Script::Script(sol::function LuaOnCreate, sol::function LuaOnUpdate, sol::function LuaOnDelete)
	{
		this->_LuaOnCreate = LuaOnCreate;
		this->_LuaOnUpdate = LuaOnUpdate;
		this->_LuaOnDelete = LuaOnDelete;
	}
}