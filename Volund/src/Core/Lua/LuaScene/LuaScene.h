#pragma once

#include "Core/Scene/Scene.h"

#include "Core/Lua/LuaEntity/LuaEntity.h"

namespace Volund
{
	class LuaScene
	{
	public:

		LuaEntity CreateEntity();

		LuaScene(Ref<Scene> scene);

	private:

		Ref<Scene> _Scene;
	};
}