#pragma once

#include "Panel.hpp"

#include <memory>
#include <string>
#include <unordered_map>

class EditorContext;

class AssetRegistry : public Panel 
{
public:
    AssetRegistry(std::shared_ptr<EditorContext> context);
    void OnProcedure(const VL::Event& e) override;
private:
    enum class AssetType 
    {
        All,
        Mesh,
        Texture,
        Shader
    };
    struct AssetTypeInfo 
    {
        std::string name;
    };
    void RenderAssetList();
    void RenderAssetEntry(const std::string& name, AssetType type);
    void HandleDragDrop();
    void HandleKeyboardShortcuts();
    void DeleteSelectedAssets();
    void RegisterAssetType(AssetType type, const std::string& name);
    std::unordered_map<AssetType, AssetTypeInfo> m_assetTypeInfo;
    std::shared_ptr<EditorContext> m_context;
    std::string m_searchFilter;
    AssetType m_currentTypeFilter = AssetType::All;
    std::unordered_map<std::string, bool> m_selectedAssets;
};