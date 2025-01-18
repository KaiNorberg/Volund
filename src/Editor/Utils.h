#pragma once

#include <string.h>

#include <Volund.h>

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
