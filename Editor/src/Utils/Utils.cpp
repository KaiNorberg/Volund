#include "PCH/PCH.h"
#include "Utils.h"

#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

namespace Utils
{
	void ImGuiStartCombo()
	{
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 100);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 2));
	}

	void ImGuiNextColumn()
	{
		ImGui::NextColumn();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);
	}

	void ImGuiEndCombo()
	{
		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::NextColumn();
	}

	void ImGuiAlign(float Width, float Alignment)
	{
		float Avail = ImGui::GetContentRegionAvail().x;
		float Off = (Avail - Width) * Alignment;
		if (Off > 0.0f)
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + Off);
	}

	std::string ImGuiStringSelector(const std::string& Name, const std::string& Default, const std::vector<std::string>& SelectableValues)
	{
		ImGuiStartCombo();

		ImGui::Text(Name.data());
		ImGuiNextColumn();

		float LineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 ButtonSize(-FLT_MIN, LineHeight);

		std::string SelectedValue;
		if (ImGui::TreeNodeEx((void*)Name.data(), ImGuiTreeNodeFlags_Framed, Default.c_str()))
		{
			for (auto& SelectableValue : SelectableValues)
			{
				if (ImGui::Button(SelectableValue.c_str(), ButtonSize))
				{
					SelectedValue = SelectableValue;
				}
			}

			ImGui::TreePop();
		}

		ImGuiEndCombo();

		if (!SelectedValue.empty())
		{
			return SelectedValue;
		}
		else
		{
			return "";
		}
	}

	std::string ImGuiFileSelector(const std::string& Name, const std::string& Default, VL::Ref<VL::Window> Owner)
	{
		ImGuiStartCombo();

		ImGui::Text(Name.data());
		ImGuiNextColumn();

		float LineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 ButtonSize(-FLT_MIN, LineHeight);

		std::string buttonLabel;
		if (Default.empty())
		{
			buttonLabel = "None";
		}
		else
		{
			buttonLabel = Default;
		}

		if (ImGui::Button(buttonLabel.c_str(), ButtonSize))
		{
			ImGuiEndCombo();
			return std::filesystem::relative(VL::Dialog::OpenFile(Owner), std::filesystem::current_path()).string();
		}

		ImGuiEndCombo();
		return std::string();
	}

	std::string ImGuiString(const std::string& Name, const std::string& Default)
	{
		ImGui::PushID((void*)Name.data());

		ImGuiStartCombo();

		ImGui::Text(Name.data());
		ImGuiNextColumn();

		std::string Value = Default;
		bool Changed = ImGui::InputText("##1234", &Value);

		ImGuiEndCombo();

		ImGui::PopID();

		if (Changed && ImGui::IsKeyPressed(ImGuiKey_Enter))
		{
			return Value;
		}
		else
		{
			return "";
		}
	}

	void ImGuiBool(const std::string& Name, bool* Value)
	{
		ImGuiStartCombo();

		ImGui::PushID((void*)Value);

		ImGui::Text(Name.c_str());
		ImGuiNextColumn();
		ImGui::Checkbox("##", Value);

		ImGui::PopID();

		ImGuiEndCombo();
	}

	void ImGuiFloat(const std::string& Name, float* Value)
	{
		ImGuiStartCombo();

		ImGui::PushID((void*)Value);

		ImGui::Text(Name.c_str());
		ImGuiNextColumn();
		ImGui::DragFloat("##", Value);

		ImGui::PopID();

		ImGuiEndCombo();
	}

	void ImGuiVec3(std::string_view Name, VL::Vec3* Value, float Speed, float DefaultValue)
	{
		ImGui::PushID((void*)Name.data());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 100);

		ImGui::Text(Name.data());
		ImGui::NextColumn();

		float LineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 ButtonSize(LineHeight + 3.0f, LineHeight);

		float spacing = 2;

		ImGui::PushMultiItemsWidths(3, ImGui::GetContentRegionAvail().x - (ButtonSize.x - spacing) * 3);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, 1));

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));

		if (ImGui::Button("X", ButtonSize))
		{
			Value->x = DefaultValue;
		}

		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &Value->x, Speed);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));

		if (ImGui::Button("Y", ButtonSize))
		{
			Value->y = DefaultValue;
		}

		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &Value->y, Speed);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));

		if (ImGui::Button("Z", ButtonSize))
		{
			Value->z = DefaultValue;
		}

		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &Value->z, Speed);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	VL::Vec2 ToScreenSpace(const VL::Mat4x4& ViewProjMatrix, const VL::Vec3& Position, const VL::Vec2& WindowPos, const VL::Vec2& WindowSize)
	{
		VL::Vec4 ScreenPosition = ViewProjMatrix * VL::Vec4(Position, 1.0f);
		ScreenPosition = (ScreenPosition / ScreenPosition.w) / 2.0f + 0.5f;
		return VL::Vec2(WindowPos.x + ScreenPosition.x * WindowSize.x, WindowPos.y + (1.0f - ScreenPosition.y) * WindowSize.y);
	}
}