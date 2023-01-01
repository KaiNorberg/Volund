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
		auto ThisEntity = sol::make_object(this->_LuaState, LuaEntity(this->GetScene(), this->GetEntity()));
		this->Table["Entity"] = ThisEntity;

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

	Script::Script(const sol::this_state& S, sol::table LuaTable, sol::table Args) : _LuaState(S)
	{
		this->_Args = Args;

		this->_LuaOnCreate = LuaTable["OnCreate"];
		this->_LuaOnUpdate = LuaTable["OnUpdate"];
		this->_LuaOnDestroy = LuaTable["OnDestroy"];

		this->_ID = (void*)LuaTable.pointer();

		this->Table = this->_LuaState.create_table_with();
		for (auto& [Key, Value] : LuaTable)
		{
			this->Table[Key] = Value;
		}
	}
}