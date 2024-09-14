#pragma once

#include <string.h>

#include <Volund.h>

#define IMGUI_DRAG_DROP_FILE "IMGUI_DRAG_DROP_FILE"
#define IMGUI_DRAG_DROP_DIR "IMGUI_DRAG_DROP_DIR"

void ImGuiStartCombo();

void ImGuiNextColumn();

void ImGuiEndCombo();

void ImGuiAlign(const std::string& text, float alignment);

bool ImGuiFile(const std::string& name, std::string& out);

bool ImGuiString(const std::string& name, std::string& out);

bool ImGuiInt(const std::string& name, int value);

bool ImGuiBool(const std::string& name, bool value);

bool ImGuiFloat(const std::string& name, float value);

bool ImGuiDouble(const std::string& name, double value);

bool ImGuiVec2(const std::string& name, VL::Vec2& value, float speed = 0.1f, float defaultValue = 0.0f);

bool ImGuiVec3(const std::string& name, VL::Vec3& value, float speed = 0.1f, float defaultValue = 0.0f);

bool ImGuiVec4(const std::string& name, VL::Vec4& value, float speed = 0.1f, float defaultValue = 0.0f);

void ImGuiColoredText(const std::string& text);

bool ImGuiListBegin(const std::string& name);

void ImGuiListEnd();

void ImGuiDragDropSource(const char* type, const std::string& payload);

std::string ImGuiDragDropTarget(const char* type);

VL::Vec2 ToScreenSpace(const VL::Mat4x4& ViewProjMatrix, const VL::Vec3& Position, const VL::Vec2& WindowPos, const VL::Vec2& WindowSize);
