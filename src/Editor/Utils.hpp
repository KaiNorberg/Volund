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

	ImGui::PushID(name.c_str());
    ImGuiStartCombo();

    ImGuiColoredText(name.c_str());
    ImGuiNextColumn();

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize(-FLT_MIN, lineHeight);

    std::string displayText;
    if (selected == nullptr)
    {
        displayText = "Select an asset...";
    }
    else
    {
        std::string key = state->GetKey(selected);
        if (key.empty())
        {
            displayText = "Invalid asset";
        }
        else
        {
            displayText = key;
        }
    }

    std::vector<std::pair<std::string, std::shared_ptr<T>>> assets;
    state->GetObjects(&assets);

    ImGui::PushItemWidth(-FLT_MIN); 
    if (ImGui::BeginCombo("##asset_selector", displayText.c_str()))
    {
        for (auto& [key, asset] : assets)
        {
            bool isSelected = (selected == asset);
            
            if (ImGui::Selectable(key.c_str(), isSelected))
            {
                output = asset;
                break;
            }

            if (isSelected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
    ImGui::PopItemWidth();

    ImGuiEndCombo();
    ImGui::PopID();

    return output;
}