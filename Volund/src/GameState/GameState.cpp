#include "PCH/PCH.h"
#include "GameState.h"

#include "Lua/LuaDeserializer/LuaDeserializer.h"

namespace Volund
{
	Ref<Scene> GameState::GetScene()
	{
		return this->m_Scene;
	}

	Ref<AssetManager> GameState::GetAssetManager()
	{
		return this->m_AssetManager;
	}

    std::string GameState::GetScenePath()
    {
        return this->m_ScenePath;
    }

    std::string GameState::GetParentPath()
    {
        if (this->m_AssetManager != nullptr)
        {
            return this->m_AssetManager->GetParentPath();
        }
        else
        {
            return "";
        }
    }

    void GameState::Procedure(const Event& e)
	{
		this->m_Input->Procedure(e);
		this->m_Scene->Procedure(e);
	}

	GameState::GameState(Ref<Dispatcher> Dispatcher, const std::string& filepath)
	{	
        this->m_ScenePath = filepath;

		this->m_Input = std::make_shared<Input>();
		this->m_ScriptingEngine = std::make_shared<ScriptingEngine>();
		this->m_AssetManager = AssetManager::Create(Dispatcher, this->m_ScenePath, this->m_ScriptingEngine);
		this->m_Scene = this->m_AssetManager->Fetch<Scene>(this->m_ScenePath);
	}

	GameState::~GameState()
	{

	}
}