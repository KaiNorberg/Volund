#include "PCH/PCH.h"
#include "Script.h"

#include "Filesystem/Filesystem.h"

namespace Volund
{
	bool Script::Compare(const sol::table other)
	{
		return this->m_ID == other.pointer();
	}

	void Script::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (e.Type)
		{
		case EventType::Update:
		{			
			float ts = VOLUND_EVENT_UPDATE_GET_TIMESTEP(e);

			if (this->m_LuaOnUpdate.valid())
			{
				try
				{		
					this->m_LuaOnUpdate(this->Table, ts);
				}
				catch (sol::error e)
				{
					VOLUND_WARNING(e.what());
				}
			}
		}
		break;
		case EventType::Render:
		{
			if (this->m_LuaOnRender.valid())
			{
				try
				{
					this->m_LuaOnRender(this->Table);
				}
				catch (sol::error e)
				{
					VOLUND_WARNING(e.what());
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
		if (this->m_LuaOnCreate.valid())
		{
			try
			{
				this->m_LuaOnCreate(this->Table, this->m_Args);
			}
			catch (sol::error e)
			{
				VOLUND_WARNING(e.what());
			}
		}
	
		this->m_Args.reset();
	}

	void Script::OnDestroy()
	{
		if (this->m_LuaOnDestroy.valid())
		{
			try
			{
				this->m_LuaOnDestroy(this->Table);
			}
			catch (sol::error e)
			{
				VOLUND_WARNING(e.what());
			}
		}
	}

	Script::Script(const sol::this_state& s, LuaEntity entity, sol::table scriptTable, const sol::table args)
	{
		sol::state_view stateView = s;

		this->m_Args = args;
		this->m_ID = (void*)scriptTable.pointer();

		this->m_LuaOnCreate = scriptTable["OnCreate"];
		this->m_LuaOnRender = scriptTable["OnRender"];
		this->m_LuaOnUpdate = scriptTable["OnUpdate"];
		this->m_LuaOnDestroy = scriptTable["OnDestroy"];

		this->Table = stateView.create_table_with();
		for (auto& [Key, Value] : scriptTable)
		{
			this->Table[Key] = Value;
		}

		this->Table["Entity"] = entity;
	}
}