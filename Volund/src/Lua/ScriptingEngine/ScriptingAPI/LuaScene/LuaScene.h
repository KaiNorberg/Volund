#pragma once

#include "Scene/Scene.h"

namespace Volund
{
	class LuaScene
	{
	public:

		int Test = 5;

		LuaScene(Ref<Scene> scene);

	private:

		Ref<Scene> m_Scene;
	};
}