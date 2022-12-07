#pragma once

#include "Core/Lua/LuaComponent/LuaComponent.h"
#include "Core/Lua/LuaComponent/LuaComponents.h"

#include "Core/Scene/Component/Script/Script.h"

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