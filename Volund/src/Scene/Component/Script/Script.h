#pragma once

#include "Scene/Component/Component.h"

namespace Volund
{
	class Script : public Component
	{
	public:

		void Procedure(const Event& E);

		void OnCreate() override;

		void OnDestroy() override;

		Script(sol::function LuaOnCreate, sol::function LuaOnUpdate, sol::function LuaOnDestroy);

	private:

		sol::function _LuaOnCreate;
		sol::function _LuaOnUpdate;
		sol::function _LuaOnDestroy;
	};
}