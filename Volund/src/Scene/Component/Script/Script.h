#pragma once

#include "Scene/Component/Component.h"
#include "Lua/LuaEntity/LuaEntity.h"

namespace Volund
{
	class Script : public Component
	{
	public:

		void Procedure(const Event& E);

		void OnCreate() override;

		void OnDestroy() override;

		Script(const sol::this_state& S, sol::table LuaTable, sol::table Args);

	private:

		sol::state_view _LuaState;

		sol::table _Args;

		sol::object _ThisEntity;

		sol::table _LuaTable;

		sol::function _LuaOnCreate;
		sol::function _LuaOnUpdate;
		sol::function _LuaOnDestroy;
	};
}