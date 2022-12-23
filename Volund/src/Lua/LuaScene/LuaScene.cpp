#include "PCH/PCH.h"
#include "LuaScene.h"

namespace Volund
{
	LuaEntity LuaScene::CreateEntity()
	{
		return LuaEntity(this->_Scene.get());
	}

	LuaScene::LuaScene(Ref<Scene> scene)
	{
		this->_Scene = scene;
	}
}