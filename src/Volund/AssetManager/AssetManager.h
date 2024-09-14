#pragma once

#include "Dispatcher/Dispatcher.h"

#include "PolyContainer/PolyContainer.h"

#include "Lua/ScriptingEngine/ScriptingEngine.h"

namespace Volund
{
    class AssetManager : public std::enable_shared_from_this<AssetManager>
    {
    public:

        std::shared_ptr<Script> LoadScript(const std::string& filepath);

        template<typename T>
        std::shared_ptr<T> Fetch(const std::string& filepath);

        template<typename T>
        std::string FetchFilepath(std::shared_ptr<T> asset);

        template<typename T>
        void Serialize(std::shared_ptr<T> asset, const std::string& destinationPath);

        std::string GetAbsolutePath(const std::string& relativePath);

        std::string GetRootDirectory();

        static std::shared_ptr<AssetManager> Create(std::shared_ptr<Dispatcher> Dispatcher, const std::string& rootPath, std::shared_ptr<ScriptingEngine> scriptingEngine = nullptr);

    private:

        AssetManager(std::shared_ptr<Dispatcher> dispatcher, const std::string& rootPath, std::shared_ptr<ScriptingEngine> scriptingEngine = nullptr);

        std::string GetRelativePath(const std::string& absolutePath);

        std::string ShortPath(const std::string& path);

        template<typename T>
        std::shared_ptr<T> Load(const std::string& filepath, uint64_t lineId);

        template<typename T>
        void Push(const std::string& filepath, std::shared_ptr<T> assetData);

        class PrimitiveAsset
        {
        public:
            std::string Filepath;

            void* Identifier = nullptr;

            virtual ~PrimitiveAsset() = default;
        };

        template<typename T>
        class Asset : public PrimitiveAsset
        {
        public:
            std::weak_ptr<T> Data;
        };

        PolyContainer<PrimitiveAsset> m_Data;

        std::string m_RootDir;

        std::shared_ptr<Dispatcher> m_Dispatcher;

        std::weak_ptr<ScriptingEngine> m_ScriptingEngine;
    };

    template<typename T>
    inline std::shared_ptr<T> AssetManager::Fetch(const std::string& filepath)
    {
        static std::mutex mutex;
        std::unique_lock lock(mutex);

        std::string absolutePath = this->GetAbsolutePath(filepath);
        std::string relativePath = this->GetRelativePath(filepath);

        if (m_Data.Contains<Asset<T>>())
        {
            auto& view = m_Data.View<Asset<T>>();

            for (int i = 0; i < view.size(); i++)
            {
                if (view[i]->Filepath == relativePath)
                {
                    auto fetchedData = std::dynamic_pointer_cast<Asset<T>>(view[i])->Data;
                    if (fetchedData.expired())
                    {
                        uint64_t lineId = VOLUND_INFO("Asset expired, retrieving new asset (%s)... ", relativePath.c_str());

                        this->m_Data.Erase<Asset<T>>(i);
                        auto asset = this->Fetch<T>(relativePath);

                        VOLUND_UPDATE_LINE(lineId, "Done");

                        return asset;
                    }

                    return fetchedData.lock();
                }
            }
        }

        uint64_t lineId = VOLUND_INFO("Loading Asset (%s)... ", relativePath.c_str());

        std::shared_ptr<T> newAssetData = this->Load<T>(absolutePath, lineId);
        this->Push(relativePath, newAssetData);

        return newAssetData;
    }

    template<typename T>
    inline std::string AssetManager::FetchFilepath(std::shared_ptr<T> asset)
    {
        if (m_Data.Contains<Asset<T>>())
        {
            auto& view = m_Data.View<Asset<T>>();

            for (int i = 0; i < view.size(); i++)
            {
                if (view[i]->Identifier == asset.get())
                {
                    return view[i]->Filepath;
                }
            }
        }

        return "";
    }

    template<typename T>
    inline void AssetManager::Push(const std::string& filepath, std::shared_ptr<T> assetData)
    {
        auto newAsset = std::make_shared<Asset<T>>();
        newAsset->Filepath = filepath;
        newAsset->Data = assetData;
        newAsset->Identifier = assetData.get();
        this->m_Data.PushBack(newAsset);
    }
}
