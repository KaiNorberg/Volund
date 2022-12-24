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

		Script(const sol::this_state& S, sol::function LuaOnCreate, sol::function LuaOnUpdate, sol::function LuaOnDestroy);

	private:

		lua_State* _LuaState;

		sol::object _ThisEntity;

		sol::function _LuaOnCreate;
		sol::function _LuaOnUpdate;
		sol::function _LuaOnDestroy;
	};
}