#include "PCH/PCH.h"
#include "GameState.h"

#include "Lua/Deserializer/Deserializer.h"

namespace Volund
{
	std::shared_ptr<Scene> GameState::GetScene()
	{
		return this->m_Scene;
	}

	void GameState::SaveScene(const std::string& filepath)
	{
		if (filepath.empty())
		{
			this->m_AssetManager->Serialize<Scene>(this->m_Scene, this->FetchFilepath<Scene>(this->m_Scene));
		}
		else
		{
			this->m_AssetManager->Serialize<Scene>(this->m_Scene, filepath);
		}
	}

	void GameState::LoadScene(const std::string& filepath)
	{
		this->m_ScriptingEngine = ScriptingEngine::Create();
		this->m_AssetManager = AssetManager::Create(this->m_Dispatcher, filepath, this->m_ScriptingEngine);
		this->m_Scene = this->m_AssetManager->Fetch<Scene>(filepath);
	}

	void GameState::ReloadScene()
	{
		std::string scenePath = this->m_AssetManager->FetchFilepath<Scene>(this->m_Scene);

		std::string absoluteScenePath = this->m_AssetManager->GetAbsolutePath(scenePath);

		this->m_ScriptingEngine = ScriptingEngine::Create();
		this->m_AssetManager = AssetManager::Create(this->m_Dispatcher, absoluteScenePath, this->m_ScriptingEngine);
		this->m_Scene = this->m_AssetManager->Fetch<Scene>(scenePath);
	}

	void GameState::Procedure(const Event& e)
	{
		this->m_Input.Procedure(e);

		this->m_Scene->Procedure(e);
	}

	CHRONO_TIME_POINT GameState::GetStartTime()
	{
		return CHRONO_TIME_POINT();
	}

	Entity GameState::AllocateEntity()
	{
		return this->m_Scene->AllocateEntity();
	}

	void GameState::DeallocateEntity(Entity entity)
	{
		this->m_Scene->DeallocateEntity(entity);
	}

	bool GameState::IsAllocated(Entity entity)
	{
		return this->m_Scene->IsAllocated(entity);
	}

	std::vector<Scene::EntityEntry>::iterator GameState::begin()
	{
		return this->m_Scene->begin();
	}

	std::vector<Scene::EntityEntry>::iterator GameState::end()
	{
		return this->m_Scene->end();
	}

	std::shared_ptr<Script> GameState::LoadScript(const std::string& filepath)
	{
		return this->m_AssetManager->LoadScript(filepath);
	}

	std::string GameState::GetRootDirectory()
	{
		return this->m_AssetManager->GetRootDirectory();
	}

	std::shared_ptr<GameState> GameState::Create(std::shared_ptr<Dispatcher> dispatcher)
	{
		return std::shared_ptr<GameState>(new GameState(dispatcher));
	}

	std::shared_ptr<GameState> GameState::Create(std::shared_ptr<Dispatcher> dispatcher, const std::string& filepath)
	{
		return std::shared_ptr<GameState>(new GameState(dispatcher, filepath));
	}

	GameState::GameState(std::shared_ptr<Dispatcher> dispatcher)
	{
		this->m_Dispatcher = dispatcher;

		this->m_ScriptingEngine = ScriptingEngine::Create();
		this->m_AssetManager = AssetManager::Create(this->m_Dispatcher, ".", this->m_ScriptingEngine);
		this->m_Scene = Scene::Create();
	}

	GameState::GameState(std::shared_ptr<Dispatcher> dispatcher, const std::string& filepath)
	{
		this->m_Dispatcher = dispatcher;

		this->LoadScene(filepath);
	}

	GameState::~GameState()
	{

	}
}
