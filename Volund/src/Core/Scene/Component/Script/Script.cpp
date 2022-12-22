#include "PCH/PCH.h"
#include "Script.h"

#include "Core/Lua/LuaEntity/LuaEntity.h"

#include "Filesystem/Filesystem.h"

namespace Volund
{
	void Script::OnCreate()
	{
		if (this->_LuaOnCreate != sol::lua_nil)
		{
			try
			{
				this->_LuaOnCreate.call<void>(LuaEntity(this->GetScene(), this->GetEntity()));
			}
			catch (sol::error E)
			{
				VOLUND_WARNING(E.what());
			}
		}
	}

	void Script::OnUpdate(TimeStep TS)
	{
		VOLUND_PROFILE_FUNCTION();

		if (this->_LuaOnUpdate != sol::lua_nil)
		{
			try
			{
				this->_LuaOnUpdate.call<void>(LuaEntity(this->GetScene(), this->GetEntity()), TS.GetSeconds());
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
				this->_LuaOnDelete.call<void>(LuaEntity(this->GetScene(), this->GetEntity()));
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