#include "PCH/PCH.h"
#include "Widget.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

#include "FileDialog/FileDialog.h"

void Widget::Align(float Width, float Alignment)
{
	float Avail = ImGui::GetContentRegionAvail().x;
	float Off = (Avail - Width) * Alignment;
	if (Off > 0.0f)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + Off);
}

std::string Widget::TextSelectorControl(const std::string& Name, const std::string& Default, const std::vector<std::string>& SelectableValues)
{
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100);

	ImGui::Text(Name.data());
	ImGui::NextColumn();
	Align(10, 0.01f);

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

	ImGui::Columns(1);

	ImGui::NextColumn();

	if (!SelectedValue.empty())
	{
		return SelectedValue;
	}
	else
	{
		return "";
	}
}

std::string Widget::FileSelectorControl(const std::string& Name, const std::string& Default, const char* Filter, Volund::Ref<Volund::Window> Owner)
{
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100);

	ImGui::Text(Name.data());
	ImGui::NextColumn();
	Align(10, 0.01f);

	float LineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 ButtonSize(-FLT_MIN, LineHeight);

	if (ImGui::Button(Default.c_str(), ButtonSize))
	{
		return std::filesystem::relative(FileDialog::OpenFile(Filter, Owner), std::filesystem::current_path()).string();
	}

	ImGui::Columns(1);

	ImGui::NextColumn();

	return std::string();
}

std::string Widget::TextControl(const std::string& Name, const std::string& Default)
{
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

	ImGui::Text(Name.data());
	ImGui::NextColumn();
	Align(10, 0.01f);

	ImGui::PushID((void*)Name.data());

	std::string Value = Default;
	bool Changed = ImGui::InputText("##1234", &Value);

	ImGui::Columns(1);

	ImGui::PopStyleVar();
	ImGui::NextColumn();

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

void Widget::BoolControl(const std::string& Name, bool* Value)
{
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

	ImGui::PushID((void*)Value);

	ImGui::Text(Name.c_str());
	ImGui::NextColumn();
	Align(10, 0.05f);
	ImGui::Checkbox("##", Value);
	ImGui::NextColumn();

	ImGui::PopID();

	ImGui::Columns(1);
	ImGui::PopStyleVar();
}

void Widget::FloatControl(const std::string& Name, float* Value)
{
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

	ImGui::PushID((void*)Value);

	ImGui::Text(Name.c_str());
	ImGui::NextColumn();
	Align(10, 0.05f);
	ImGui::DragFloat("##", Value);
	ImGui::NextColumn();

	ImGui::PopID();

	ImGui::Columns(1);
	ImGui::PopStyleVar();
}

void Widget::Vec3Control(std::string_view Name, Volund::Vec3* Value, float Speed, float DefaultValue)
{
	ImGui::PushID((void*)Name.data());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100);

	ImGui::Text(Name.data());
	ImGui::NextColumn();

	float LineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 ButtonSize(LineHeight + 3.0f, LineHeight);

	ImGui::PushMultiItemsWidths(3, ImGui::GetContentRegionAvail().x - ButtonSize.x * 3);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

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