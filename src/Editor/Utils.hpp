#pragma once

#include <string.h>

#include <Volund/Volund.hpp>

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

#define IMGUI_DRAG_DROP_FILE "IMGUI_DRAG_DROP_FILE"
#define IMGUI_DRAG_DROP_DIR "IMGUI_DRAG_DROP_DIR"

void ImGuiStartCombo();

void ImGuiNextColumn();

void ImGuiEndCombo();

void ImGuiAlign(std::string const& text, float alignment);

bool ImGuiFile(std::string const& name, std::string& out);

bool ImGuiString(std::string const& name, std::string& out);

bool ImGuiInt(std::string const& name, int value);

bool ImGuiBool(std::string const& name, bool value);

bool ImGuiFloat(std::string const& name, float value);

bool ImGuiDouble(std::string const& name, double value);

bool ImGuiVec2(std::string const& name, VL::Vec2& value, float speed = 0.1f, float defaultValue = 0.0f);

bool ImGuiVec3(std::string const& name, VL::Vec3& value, float speed = 0.1f, float defaultValue = 0.0f);

bool ImGuiVec4(std::string const& name, VL::Vec4& value, float speed = 0.1f, float defaultValue = 0.0f);

void ImGuiColoredText(std::string const& text);

bool ImGuiListBegin(std::string const& name);

void ImGuiListEnd();

void ImGuiDragDropSource(const char* type, std::string const& payload);

std::string ImGuiDragDropTarget(const char* type);

VL::Vec2 ToScreenSpace(const VL::Mat4x4& ViewProjMatrix, const VL::Vec3& pos, const VL::Vec2& WindowPos, const VL::Vec2& WindowSize);

template<typename T>
std::shared_ptr<T> ImGuiAssetSelector(const std::string& name, std::shared_ptr<T> selected, std::shared_ptr<VL::LuaState> state)
{
    std::shared_ptr<T> output = nullptr;
    static std::string searchBuffer;
    
    ImGui::PushID(name.c_str());
    ImGuiStartCombo();

    ImGuiColoredText(name);
    ImGuiNextColumn();

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize(-FLT_MIN, lineHeight);

    std::string displayText = selected ? state->GetKey(selected) : "Select an asset...";
    if (selected && displayText.empty())
    {
        displayText = "Invalid asset";
    }

    std::vector<std::pair<std::string, std::shared_ptr<T>>> assets;
    state->GetObjects(&assets);

    ImGui::PushItemWidth(-FLT_MIN);
    if (ImGui::BeginCombo("##asset_selector", displayText.c_str()))
    {
        float searchWidth = ImGui::GetContentRegionAvail().x - 20;
        
        ImGui::SetNextItemWidth(searchWidth);
        bool searchChanged = ImGui::InputText("##search", &searchBuffer, 
            ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EscapeClearsAll);
        
        if (ImGui::IsWindowAppearing())
        {
            ImGui::SetKeyboardFocusHere(-1);
        }
        
        if (!searchBuffer.empty())
        {
            ImGui::SameLine();
            if (ImGui::SmallButton("×"))
            {
                searchBuffer.clear();
                searchChanged = true;
            }
        }
        
        ImGui::Separator();

        bool hasVisibleItems = false;
        
        for (auto& [key, asset] : assets)
        {
            if (!searchBuffer.empty())
            {
                std::string lowerKey = key;
                std::string lowerSearch = searchBuffer;
                std::transform(lowerKey.begin(), lowerKey.end(), lowerKey.begin(), ::tolower);
                std::transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), ::tolower);
                
                if (lowerKey.find(lowerSearch) == std::string::npos)
                {
                    continue;
                }
            }
            
            hasVisibleItems = true;
            bool isSelected = (selected == asset);
            
            if (!searchBuffer.empty())
            {
                size_t matchPos = key.find(searchBuffer);
                if (matchPos != std::string::npos)
                {
                    std::string before = key.substr(0, matchPos);
                    std::string match = key.substr(matchPos, searchBuffer.length());
                    std::string after = key.substr(matchPos + searchBuffer.length());
                    
                    ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_TextDisabled]);
                    ImGui::Selectable(before.c_str(), false, ImGuiSelectableFlags_Disabled);
                    ImGui::SameLine(0, 0);
                    
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f));
                    ImGui::Selectable(match.c_str(), false, ImGuiSelectableFlags_Disabled);
                    ImGui::PopStyleColor();
                    
                    ImGui::SameLine(0, 0);
                    ImGui::Selectable(after.c_str(), false, ImGuiSelectableFlags_Disabled);
                    ImGui::PopStyleColor();
                    
                    ImGui::SetCursorPosY(ImGui::GetCursorPosY() - lineHeight);
                    if (ImGui::Selectable("##select", isSelected, 0, ImVec2(-1, lineHeight)))
                    {
                        output = asset;
                    }
                }
                else
                {
                    if (ImGui::Selectable(key.c_str(), isSelected))
                    {
                        output = asset;
                    }
                }
            }
            else
            {
                if (ImGui::Selectable(key.c_str(), isSelected))
                {
                    output = asset;
                }
            }

            if (isSelected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        
        if (!hasVisibleItems && !searchBuffer.empty())
        {
            ImGui::TextColored(ImGui::GetStyle().Colors[ImGuiCol_TextDisabled], "No matching assets found");
        }
        
        ImGui::EndCombo();
    }
    else if (!ImGui::IsPopupOpen(""))
    {
        searchBuffer.clear();
    }
    ImGui::PopItemWidth();

    ImGuiEndCombo();
    ImGui::PopID();

    return output;
}