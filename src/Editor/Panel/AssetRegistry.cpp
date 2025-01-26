#include "AssetRegistry.hpp"
#include "Editor.hpp"
#include <imgui.h>
#include <imgui_internal.h>

void AssetRegistry::OnProcedure(const VL::Event& e)
{
    if (e.type != VOLUND_EVENT_RENDER)
    {
        return;
    }

    ImGui::Text("Search:");
    ImGui::SameLine();
    
    ImGui::SetNextItemWidth(150);
    ImGui::InputText("##Search", &m_searchFilter);
    
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    
    if (ImGui::BeginCombo("##FilterCombo", m_assetTypeInfo[m_currentTypeFilter].name.c_str()))
    {
        for (const auto& [type, info] : m_assetTypeInfo)
        {
            bool is_selected = (m_currentTypeFilter == type);
            if (ImGui::Selectable(info.name.c_str(), is_selected))
                m_currentTypeFilter = type;
                
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    ImGui::SameLine();
    bool hasSelection = std::any_of(m_selectedAssets.begin(), m_selectedAssets.end(),
        [](const auto& pair) { return pair.second; });
    
    if (ImGui::Button("Delete") && hasSelection)
    {
        ImGui::OpenPopup("Delete Assets?");
    }

    HandleDragDrop();
    HandleKeyboardShortcuts();

    ImGui::Separator();
    RenderAssetList();

    if (ImGui::BeginPopupModal("Delete Assets?", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Are you sure you want to delete the selected assets?");
        ImGui::Text("This operation cannot be undone.");
        
        ImGui::Separator();
        
        if (ImGui::Button("Yes", ImVec2(120, 0)) || ImGui::IsKeyPressed(ImGuiKey_Enter))
        {
            // TODO: Actually delete the assets
            for (const auto& [name, selected] : m_selectedAssets)
            {
                if (selected)
                {
                    VOLUND_INFO("Would delete asset: {}", name);
                }
            }
            m_selectedAssets.clear();
            ImGui::CloseCurrentPopup();
        }
        
        ImGui::SameLine();
        if (ImGui::Button("No", ImVec2(120, 0)) || ImGui::IsKeyPressed(ImGuiKey_Escape))
        {
            ImGui::CloseCurrentPopup();
        }
        
        ImGui::EndPopup();
    }
}

void AssetRegistry::RenderAssetList()
{
    static ImGuiTableFlags flags = 
        ImGuiTableFlags_ScrollY | 
        ImGuiTableFlags_RowBg | 
        ImGuiTableFlags_BordersOuter | 
        ImGuiTableFlags_BordersV |
        ImGuiTableFlags_Resizable;

    if (ImGui::BeginTable("AssetsTable", 2, flags))
    {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableHeadersRow();

        ImVec4 altRowColor = ImGui::GetStyle().Colors[ImGuiCol_TableRowBgAlt];
        altRowColor.x *= 0.8f;
        altRowColor.y *= 0.8f;
        altRowColor.z *= 0.8f;
        
        ImVec4 origSelectionColor = ImGui::GetStyle().Colors[ImGuiCol_Header];
        ImGui::GetStyle().Colors[ImGuiCol_Header] = ImVec4(0.3f, 0.4f, 0.7f, 1.0f);

        ImVec2 tableMin = ImGui::GetWindowPos();
        ImVec2 tableMax = ImVec2(tableMin.x + ImGui::GetWindowSize().x, 
                                tableMin.y + ImGui::GetWindowSize().y);

        // TODO: Replace with actual asset iteration
        RenderAssetEntry("DefaultCube", AssetType::Mesh);
        RenderAssetEntry("SkyboxTexture", AssetType::Texture);
        RenderAssetEntry("BasicShader", AssetType::Shader);

        ImGui::GetStyle().Colors[ImGuiCol_Header] = origSelectionColor;

        if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            ImVec2 mousePos = ImGui::GetMousePos();
            if (mousePos.x >= tableMin.x && mousePos.x <= tableMax.x &&
                mousePos.y >= tableMin.y && mousePos.y <= tableMax.y)
            {
                m_selectedAssets.clear();
            }
        }

        ImGui::EndTable();
    }
}

void AssetRegistry::RenderAssetEntry(const std::string& name, AssetType type)
{
    if (m_currentTypeFilter != AssetType::All && m_currentTypeFilter != type)
        return;

    if (!m_searchFilter.empty() && name.find(m_searchFilter) == std::string::npos)
        return;

    ImGui::TableNextRow();
    
    ImGui::TableNextColumn();
    
    ImGui::PushID(name.c_str());
    bool isSelected = m_selectedAssets[name];
    if (ImGui::Selectable(name.c_str(), &isSelected, ImGuiSelectableFlags_SpanAllColumns))
    {
        if (!ImGui::GetIO().KeyCtrl && !ImGui::GetIO().KeyShift)
        {
            m_selectedAssets.clear();
        }
        m_selectedAssets[name] = isSelected;
    }
    ImGui::PopID();
    
    if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
    {
        // TODO: Open in appropriate editor
        VOLUND_INFO("Double clicked asset: {}", name);
    }

    ImGui::TableNextColumn();
    ImGui::Text("%s", m_assetTypeInfo[type].name.c_str());
}

void AssetRegistry::HandleKeyboardShortcuts()
{
    if (!ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
        return;

    if (ImGui::IsKeyPressed(ImGuiKey_Delete))
    {
        DeleteSelectedAssets();
    }

    if (ImGui::GetIO().KeyCtrl && ImGui::IsKeyPressed(ImGuiKey_A))
    {
        // TODO: Iterate through actual assets instead of example data
        m_selectedAssets["DefaultCube"] = true;
        m_selectedAssets["SkyboxTexture"] = true;
        m_selectedAssets["BasicShader"] = true;
    }
}

void AssetRegistry::DeleteSelectedAssets()
{
    if (m_selectedAssets.empty())
        return;

    ImGui::OpenPopup("Delete Assets?");
}

void AssetRegistry::HandleDragDrop()
{
    if (ImGui::BeginDragDropTarget())
    {
        const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_DRAG_DROP_FILE);
        if (payload)
        {
            std::string filepath((const char*)payload->Data);
            // TODO: Handle file loading based on extension
            VOLUND_INFO("File dropped: {}", filepath);
        }
        ImGui::EndDragDropTarget();
    }
}

void AssetRegistry::RegisterAssetType(AssetType type, const std::string& name)
{
    m_assetTypeInfo[type] = AssetTypeInfo{
        name
    };
}

AssetRegistry::AssetRegistry(std::shared_ptr<EditorContext> context)
    : m_context(context)
{
    this->SetName("Registry");

    RegisterAssetType(AssetType::All, "All");
    RegisterAssetType(AssetType::Mesh, "Meshes");
    RegisterAssetType(AssetType::Texture, "Textures");
    RegisterAssetType(AssetType::Shader, "Shaders");
}