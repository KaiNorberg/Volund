#pragma once

#include "Lua/LuaComponent/LuaComponent.h"
#include "Lua/LuaComponent/LuaComponents.h"

#include "Scene/Component/Script/Script.h"

namespace Volund
{
	struct LuaScript
	{
	public:

		LuaScript(Ref<Script> Script);

	private:

		Ref<Script> _Script;
	};
}