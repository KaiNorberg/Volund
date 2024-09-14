#include "PCH/PCH.h"

#include "LuaScene.h"

namespace Volund
{
	LuaScene::LuaScene(std::shared_ptr<Scene> scene)
	{
		this->m_Scene = scene;
	}
}
