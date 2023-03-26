#pragma once

#include "Scene/Component/Component.h"
#include "Lua/LuaEntity/LuaEntity.h"

namespace Volund
{
	class Script : public Component
	{
	public:

		sol::table Table;

		bool Compare(sol::table other);

		void Procedure(const Event& e);

		void OnCreate() override;

		void OnDestroy() override;

		Script(const sol::this_state& s, LuaEntity entity, sol::table scriptTable, sol::table args);

	private:

		sol::table m_Args;

		sol::object m_ThisEntity;

		sol::safe_function m_LuaOnCreate;
		sol::safe_function m_LuaOnUpdate;
		sol::safe_function m_LuaOnRender;
		sol::safe_function m_LuaOnDestroy;

		void* m_ID;
	};
}