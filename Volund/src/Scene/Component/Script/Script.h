#pragma once

#include "Scene/Component/Component.h"
#include "Lua/LuaEntity/LuaEntity.h"

namespace Volund
{
	class Script : public Component
	{
	public:

		sol::table Table;

		bool Compare(sol::table Other);

		void Procedure(const Event& E);

		void OnCreate() override;

		void OnDestroy() override;

		Script(const sol::this_state& S, LuaEntity ThisEntity, sol::table ScriptTable, sol::table Args);

	private:

		sol::table _Args;

		sol::object _ThisEntity;

		sol::safe_function _LuaOnCreate;
		sol::safe_function _LuaOnUpdate;
		sol::safe_function _LuaOnDestroy;

		void* _ID;
	};
}