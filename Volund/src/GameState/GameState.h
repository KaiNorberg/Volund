#pragma once

#include "Input/Input.h"
#include "Scene/Scene.h"
#include "Window/Window.h"
#include "AssetManager/AssetManager.h"

#include "Lua/ScriptingEngine/ScriptingEngine.h"

namespace Volund
{
	class GameState
	{
	public:

		Ref<Scene> GetScene();

		void SaveScene(const std::string& filepath = "");

		void LoadScene(const std::string& filepath);

		void ReloadScene();

		void Procedure(const Event& e);

		CHRONO_TIME_POINT GetStartTime();

		Entity AllocateEntity();

		void DeallocateEntity(Entity entity);

		bool IsAllocated(Entity entity);

		template<typename T, typename... Args>
		Ref<T> CreateComponent(Entity entity, Args&&... args);

		template<typename T>
		void DeleteComponent(Entity entity, uint64_t index = 0);

		template<typename T>
		bool HasComponent(Entity entity, uint64_t index = 0);

		template<typename T>
		uint64_t ComponentAmount(Entity entity);

		template<typename T>
		Ref<T> GetComponent(Entity entity, uint64_t index = 0);

		template<typename T>
		Ref<T> FetchAsset(const std::string& filepath);

		template<typename T>
		std::string FetchFilepath(Ref<T> asset);

		template<typename T>
		void Serialize(Ref<T> asset, const std::string& filepath);

		Ref<Script> LoadScript(const std::string& filepath);

		std::string GetRootDirectory();

		std::vector<Scene::EntityEntry>::iterator begin();
		std::vector<Scene::EntityEntry>::iterator end();

		GameState(Ref<Dispatcher> dispatcher);
		GameState(Ref<Dispatcher> dispatcher, const std::string& filepath);

		~GameState();

	private:

		std::mutex m_Mutex;

		Ref<Dispatcher> m_Dispatcher;
		Ref<Input> m_Input;

		Ref<Scene> m_Scene;
		Ref<AssetManager> m_AssetManager;	
		Ref<ScriptingEngine> m_ScriptingEngine;
	};

	template<typename T, typename ...Args>
	inline Ref<T> GameState::CreateComponent(Entity entity, Args&&... args)
	{
		return this->m_Scene->CreateComponent<T>(entity, std::forward<Args>(args)...);
	}

	template<typename T>
	inline void GameState::DeleteComponent(Entity entity, uint64_t index)
	{
		this->m_Scene->DeleteComponent<T>(entity, index);
	}

	template<typename T>
	inline bool GameState::HasComponent(Entity entity, uint64_t index)
	{
		return this->m_Scene->HasComponent<T>(entity, index);
	}

	template<typename T>
	inline uint64_t GameState::ComponentAmount(Entity entity)
	{
		return this->m_Scene->ComponentAmount<T>(entity);
	}

	template<typename T>
	inline Ref<T> GameState::GetComponent(Entity entity, uint64_t index)
	{
		return this->m_Scene->GetComponent<T>(entity, index);
	}

	template<typename T>
	inline Ref<T> GameState::FetchAsset(const std::string& filepath)
	{
		return this->m_AssetManager->Fetch<T>(filepath);
	}

	template<typename T>
	inline std::string GameState::FetchFilepath(Ref<T> asset)
	{
		return this->m_AssetManager->FetchFilepath<T>(asset);
	}

	template<typename T>
	inline void GameState::Serialize(Ref<T> asset, const std::string& filepath)
	{
		this->m_AssetManager->Serialize<T>(asset, filepath);
	}
}

