#include "PCH/PCH.h"
#include "GameState.h"

namespace Volund
{
	Ref<Scene> GameState::GetScene()
	{
		return this->_Scene;
	}

	Ref<LuaState> GameState::GetLuaState()
	{
		return this->_LuaState;
	}

	void GameState::Procedure(const Event& E)
	{
		this->_Input->Procedure(E);
		this->_Scene->Procedure(E);
	}

	GameState::GameState(Ref<Window> GameWindow)
	{
		this->_Input = std::make_shared<Input>();
		this->_Scene = std::make_shared<Scene>();
		this->_LuaState = std::make_shared<LuaState>(this->_Scene, this->_Input, GameWindow);
	}

	GameState::~GameState()
	{
		this->_Input.reset();
		this->_Scene.reset();
		this->_LuaState.reset();
	}
}