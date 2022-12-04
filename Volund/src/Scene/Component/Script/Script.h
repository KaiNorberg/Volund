#pragma once

#include "Scene/Component/Component.h"

namespace Volund
{
	class Script : public Component
	{
	public:

		void OnUpdate(TimeStep TS);

		Script() = default;

		Script(std::string Filepath);

	private:

		Ref<sol::state> _Lua;
	};
}