#include "PCH/PCH.h"
#include "Script.h"

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

			if (this->_LuaOnUpdate.valid())
			{
				try
				{		
					this->_LuaOnUpdate(this->_LuaTable, TS);
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
		auto ThisEntity = sol::make_object(this->_LuaState, LuaEntity(this->GetScene(), this->GetEntity()));
		this->_LuaTable["Entity"] = ThisEntity;

		if (this->_LuaOnCreate.valid())
		{
			try
			{
				this->_LuaOnCreate(this->_LuaTable, this->_Args);
			}
			catch (sol::error E)
			{
				VOLUND_WARNING(E.what());
			}
		}
	
		this->_Args.reset();
	}

	void Script::OnDestroy()
	{
		if (this->_LuaOnDestroy.valid())
		{
			try
			{
				this->_LuaOnDestroy(this->_LuaTable);
			}
			catch (sol::error E)
			{
				VOLUND_WARNING(E.what());
			}
		}
	}

	Script::Script(const sol::this_state& S, sol::table Table, sol::table Args) : _LuaState(S)
	{
		this->_Args = Args;

		this->_LuaOnCreate = Table["OnCreate"];
		this->_LuaOnUpdate = Table["OnUpdate"];
		this->_LuaOnDestroy = Table["OnDestroy"];

		this->_LuaTable = this->_LuaState.create_table_with();
		for (auto& [Key, Value] : Table)
		{
			this->_LuaTable[Key] = Value;
		}
	}
}