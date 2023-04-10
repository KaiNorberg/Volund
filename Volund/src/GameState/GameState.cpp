#include "PCH/PCH.h"
#include "GameState.h"

#include "ThreadPool/ThreadPool.h"
#include "Lua/LuaState/LuaScene/LuaScene.h"

namespace Volund
{
	Ref<Scene> GameState::GetScene()
	{
		return this->m_Scene;
	}

	void GameState::Procedure(const Event& e)
	{
		this->m_Input->Procedure(e);
		this->m_Scene->Procedure(e);
	}

	GameState::GameState(const std::string& filepath)
	{	
		while (VOLUND_THREADPOOL_BUSY());	

		this->m_FilesystemLink = FilesystemLink::Create(std::filesystem::path(filepath).parent_path().string());

		LuaScene luaScene = LuaScene(filepath);

		this->m_Input = std::make_shared<Input>();
		this->m_Scene = luaScene.Get();
	}

	GameState::~GameState()
	{

	}
}