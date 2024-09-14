#pragma once

#include "Input.h"
#include "Scene/Scene.h"
#include "Window/Window.h"
#include "AssetManager/AssetManager.h"

#include "Lua/ScriptingEngine/ScriptingEngine.h"

namespace Volund
{
    class GameState
    {
    public:

        std::shared_ptr<Scene> GetScene();

        void SaveScene(const std::string& filepath = "");

        void LoadScene(const std::string& filepath);

        void ReloadScene();

        void Procedure(const Event& e);

        CHRONO_TIME_POINT GetStartTime();

        Entity AllocateEntity();

        void DeallocateEntity(Entity entity);

        bool IsAllocated(Entity entity);

        template<typename T, typename... Args>
        std::shared_ptr<T> CreateComponent(Entity entity, Args&&... args);

        template<typename T>
        void DeleteComponent(Entity entity, uint64_t index = 0);

        template<typename T>
        bool HasComponent(Entity entity, uint64_t index = 0);

        template<typename T>
        uint64_t ComponentAmount(Entity entity);

        template<typename T>
        std::shared_ptr<T> GetComponent(Entity entity, uint64_t index = 0);

        template<typename T>
        std::shared_ptr<T> FetchAsset(const std::string& filepath);

        template<typename T>
        std::string FetchFilepath(std::shared_ptr<T> asset);

        template<typename T>
        void Serialize(std::shared_ptr<T> asset, const std::string& filepath);

        std::shared_ptr<Script> LoadScript(const std::string& filepath);

        std::string GetRootDirectory();

        std::vector<Scene::EntityEntry>::iterator begin();
        std::vector<Scene::EntityEntry>::iterator end();

        static std::shared_ptr<GameState> Create(std::shared_ptr<Dispatcher> dispatcher);
        static std::shared_ptr<GameState> Create(std::shared_ptr<Dispatcher> dispatcher, const std::string& filepath);

        ~GameState();

    private:

        GameState(std::shared_ptr<Dispatcher> dispatcher);
        GameState(std::shared_ptr<Dispatcher> dispatcher, const std::string& filepath);

        std::mutex m_Mutex;

        Input m_Input;

        std::shared_ptr<Dispatcher> m_Dispatcher;

        std::shared_ptr<Scene> m_Scene;
        std::shared_ptr<AssetManager> m_AssetManager;
        std::shared_ptr<ScriptingEngine> m_ScriptingEngine;
    };

    template<typename T, typename ...Args>
    inline std::shared_ptr<T> GameState::CreateComponent(Entity entity, Args&&... args)
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
    inline std::shared_ptr<T> GameState::GetComponent(Entity entity, uint64_t index)
    {
        return this->m_Scene->GetComponent<T>(entity, index);
    }

    template<typename T>
    inline std::shared_ptr<T> GameState::FetchAsset(const std::string& filepath)
    {
        return this->m_AssetManager->Fetch<T>(filepath);
    }

    template<typename T>
    inline std::string GameState::FetchFilepath(std::shared_ptr<T> asset)
    {
        return this->m_AssetManager->FetchFilepath<T>(asset);
    }

    template<typename T>
    inline void GameState::Serialize(std::shared_ptr<T> asset, const std::string& filepath)
    {
        this->m_AssetManager->Serialize<T>(asset, filepath);
    }
}
