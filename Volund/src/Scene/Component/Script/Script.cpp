#include "PCH/PCH.h"
#include "Script.h"

#include "Lua/LuaEntity/LuaEntity.h"

#include "Filesystem/Filesystem.h"

namespace Volund
{
	void Script::Procedure(const Event& E)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (E.Type)
		{
		case EventType::UPDATE:
		{			
			float TS = VOLUND_EVENT_UPDATE_GET_TIMESTEP(E);

			if (this->_LuaOnUpdate != sol::lua_nil)
			{
				try
				{
					this->_LuaOnUpdate.call<void>(LuaEntity(this->GetScene(), this->GetEntity()), TS);
				}
				catch (sol::error E)
				{
					VOLUND_WARNING(E.what());
				}
			}
		}
		break;
		default:
		{

		}
		break;
		}
	}

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

	void Script::OnDestroy()
	{
		if (this->_LuaOnDestroy != sol::lua_nil)
		{
			try
			{
				this->_LuaOnDestroy.call<void>(LuaEntity(this->GetScene(), this->GetEntity()));
			}
			catch (sol::error E)
			{
				VOLUND_WARNING(E.what());
			}
		}
	}

	Script::Script(sol::function LuaOnCreate, sol::function LuaOnUpdate, sol::function LuaOnDestroy)
	{
		this->_LuaOnCreate = LuaOnCreate;
		this->_LuaOnUpdate = LuaOnUpdate;
		this->_LuaOnDestroy = LuaOnDestroy;
	}
}