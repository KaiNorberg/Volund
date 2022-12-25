#include "PCH/PCH.h"
#include "LuaScene.h"

namespace Volund
{
	float LuaScene::TimeSinceStart()
	{
		std::chrono::duration<double> Duration = std::chrono::high_resolution_clock::now() - this->_Scene->GetStartTime();

		return Duration.count();
	}

	LuaEntity LuaScene::CreateEntity()
	{
		return LuaEntity(this->_Scene.get());
	}

	LuaScene::LuaScene(Ref<Scene> scene)
	{
		this->_Scene = scene;
	}
}