#pragma once

#include "Scene/Scene.h"

#include "Lua/LuaEntity/LuaEntity.h"

namespace Volund
{
	class LuaScene
	{
	public:

		int Padding;

		float TimeSinceStart();

		LuaEntity CreateEntity();

		LuaScene(Ref<Scene> scene);

	private:

		Ref<Scene> _Scene;
	};
}