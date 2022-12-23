#pragma once

#include "Scene/Component/Component.h"

namespace Volund
{
	class Script : public Component
	{
	public:

		void OnCreate() override;

		void OnUpdate(TimeStep TS) override;

		void OnDelete() override;

		Script(sol::function LuaOnCreate, sol::function LuaOnUpdate, sol::function LuaOnDelete);

	private:

		sol::function _LuaOnCreate;
		sol::function _LuaOnUpdate;
		sol::function _LuaOnDelete;
	};
}