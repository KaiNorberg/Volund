#include "PCH/PCH.h"
#include "Script.h"

#include "Filesystem/Filesystem.h"

namespace Volund
{
	bool Script::Compare(sol::table Other)
	{
		return this->_ID == Other.pointer();
	}

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
					this->_LuaOnUpdate(this->Table, TS);
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
		if (this->_LuaOnCreate.valid())
		{
			try
			{
				this->_LuaOnCreate(this->Table, this->_Args);
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
				this->_LuaOnDestroy(this->Table);
			}
			catch (sol::error E)
			{
				VOLUND_WARNING(E.what());
			}
		}
	}

	Script::Script(const sol::this_state& S, LuaEntity ThisEntity, sol::table ScriptTable, sol::table Args)
	{
		sol::state_view StateView = S;

		this->_Args = Args;
		this->_ID = (void*)ScriptTable.pointer();

		this->_LuaOnCreate = ScriptTable["OnCreate"];
		this->_LuaOnUpdate = ScriptTable["OnUpdate"];
		this->_LuaOnDestroy = ScriptTable["OnDestroy"];

		this->Table = StateView.create_table_with();
		for (auto& [Key, Value] : ScriptTable)
		{
			this->Table[Key] = Value;
		}

		this->Table["Entity"] = ThisEntity;
	}
}