#include "PCH/PCH.h"

#include "LuaScene.h"

namespace Volund
{
	LuaScene::LuaScene(Ref<Scene> scene)
	{
		this->m_Scene = scene;
	}
}