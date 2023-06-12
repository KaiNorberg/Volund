#pragma once

namespace Utils
{
	void ImGuiStartCombo();

	void ImGuiNextColumn();

	void ImGuiEndCombo();

	void ImGuiAlign(float Width, float Alignment);

	std::string ImGuiStringSelector(const std::string& Name, const std::string& Default, const std::vector<std::string>& SelectableValues);

	std::string ImGuiString(const std::string& Name, const std::string& Default);

	std::string ImGuiFileSelector(const std::string& Name, const std::string& Default, VL::Ref<VL::Window> Owner);

	void ImGuiBool(const std::string& Name, bool* Value);

	void ImGuiFloat(const std::string& Name, float* Value);

	void ImGuiVec3(std::string_view Name, VL::Vec3* Value, float Speed = 0.1f, float DefaultValue = 0.0f);

	VL::Vec2 ToScreenSpace(const VL::Mat4x4& ViewProjMatrix, const VL::Vec3& Position, const VL::Vec2& WindowPos, const VL::Vec2& WindowSize);
}