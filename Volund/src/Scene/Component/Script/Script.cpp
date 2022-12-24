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

			if (this->_LuaState && this->_LuaOnUpdate.valid())
			{
				try
				{		
					this->_LuaOnUpdate(this->_ThisEntity, TS);
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
		this->_ThisEntity = sol::make_object(this->_LuaState, LuaEntity(this->GetScene(), this->GetEntity()));

		if (this->_LuaOnCreate.valid())
		{
			try
			{
				this->_LuaOnCreate(this->_ThisEntity);
			}
			catch (sol::error E)
			{
				VOLUND_WARNING(E.what());
			}
		}
	}

	void Script::OnDestroy()
	{
		if (this->_LuaOnDestroy.valid())
		{
			try
			{
				this->_LuaOnDestroy(this->_ThisEntity);
			}
			catch (sol::error E)
			{
				VOLUND_WARNING(E.what());
			}
		}
	}

	Script::Script(const sol::this_state& S, sol::function LuaOnCreate, sol::function LuaOnUpdate, sol::function LuaOnDestroy)
	{
		this->_LuaState = S;

		this->_LuaOnCreate = LuaOnCreate;
		this->_LuaOnUpdate = LuaOnUpdate;
		this->_LuaOnDestroy = LuaOnDestroy;
	}
}