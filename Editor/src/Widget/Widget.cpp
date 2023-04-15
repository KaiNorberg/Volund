#include "PCH/PCH.h"

#include "Widget.h"

#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

void Widget::StartCombo()
{
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 2));
}

void Widget::NextColumn()
{
	ImGui::NextColumn();
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);
}

void Widget::EndCombo()
{
	ImGui::PopStyleVar();
	ImGui::Columns(1);
	ImGui::NextColumn();
}

void Widget::Align(float Width, float Alignment)
{
	float Avail = ImGui::GetContentRegionAvail().x;
	float Off = (Avail - Width) * Alignment;
	if (Off > 0.0f)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + Off);
}

void Widget::DrawText(const std::string& string)
{
	ImGuiStyle* style = &ImGui::GetStyle();

	const ImVec4 oldTextColor = style->Colors[ImGuiCol_Text];

	std::string outputString;
	outputString.reserve(string.size());
	for (int i = 0; i < string.size(); i++)
	{
		if (i - string.size() > 5 && string[i] == '\033'
			&& string[i + 1] == '[' && string[i + 2] == '3' && string[i + 4] == 'm')
		{
			if (!outputString.empty())
			{
				ImGui::Text(outputString.c_str());
				ImGui::SameLine();
				outputString.clear();
			}

			switch (string[i + 3])
			{
			case VOLUND_LOGGERCOLOR_BLACK[3]:
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
			}
			break;
			case VOLUND_LOGGERCOLOR_RED[3]:
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.8f, 0.1f, 0.1f, 1.00f);
			}
			break;
			case VOLUND_LOGGERCOLOR_GREEN[3]:
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.42f * 1.5f, 0.52f * 1.5f, 0.36f * 1.5f, 1.00f);
			}
			break;
			case VOLUND_LOGGERCOLOR_YELLOW[3]:
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.8f, 0.6f, 0.0f, 1.00f);
			}
			break;
			case VOLUND_LOGGERCOLOR_BLUE[3]:
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.36f, 0.68f, 0.93f, 1.00f);
			}
			break;
			case VOLUND_LOGGERCOLOR_MAGENTA[3]:
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.55f, 0.1f, 0.5f, 1.00f);
			}
			break;
			case VOLUND_LOGGERCOLOR_CYAN[3]:
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.1f, 0.6f, 0.9f, 1.00f);
			}
			break;
			case VOLUND_LOGGERCOLOR_WHITE[3]:
			{
				style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
			}
			break;
			}
			i += 4;
		}
		else
		{
			outputString.push_back(string[i]);
		}
	}

	if (!outputString.empty())
	{
		ImGui::Text(outputString.c_str());
	}

	style->Colors[ImGuiCol_Text] = oldTextColor;
}

std::string Widget::TextSelectorControl(const std::string& Name, const std::string& Default, const std::vector<std::string>& SelectableValues)
{
	StartCombo();

	ImGui::Text(Name.data());
	NextColumn();

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

	EndCombo();

	if (!SelectedValue.empty())
	{
		return SelectedValue;
	}
	else
	{
		return "";
	}
}

std::string Widget::FileSelectorControl(const std::string& Name, const std::string& Default, VL::Ref<VL::Window> Owner)
{
	StartCombo();

	ImGui::Text(Name.data());
	NextColumn();

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
		EndCombo();
		return std::filesystem::relative(VL::Dialog::OpenFile( Owner), std::filesystem::current_path()).string();
	}

	EndCombo();
	return std::string();
}

std::string Widget::TextControl(const std::string& Name, const std::string& Default)
{
	ImGui::PushID((void*)Name.data());

	StartCombo();

	ImGui::Text(Name.data());
	NextColumn();

	std::string Value = Default;
	bool Changed = ImGui::InputText("##1234", &Value);

	EndCombo();

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
	StartCombo();

	ImGui::PushID((void*)Value);

	ImGui::Text(Name.c_str());
	NextColumn();
	ImGui::Checkbox("##", Value);

	ImGui::PopID();

	EndCombo();
}

void Widget::FloatControl(const std::string& Name, float* Value)
{
	StartCombo();

	ImGui::PushID((void*)Value);

	ImGui::Text(Name.c_str());
	NextColumn();
	ImGui::DragFloat("##", Value);

	ImGui::PopID();

	EndCombo();
}

void Widget::Vec3Control(std::string_view Name, VL::Vec3* Value, float Speed, float DefaultValue)
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

VL::Vec2 Widget::ToScreenSpace(const VL::Mat4x4& ViewProjMatrix, const VL::Vec3& Position, const VL::Vec2& WindowPos, const VL::Vec2& WindowSize)
{
	VL::Vec4 ScreenPosition = ViewProjMatrix * VL::Vec4(Position, 1.0f);
	ScreenPosition = (ScreenPosition / ScreenPosition.w) / 2.0f + 0.5f;
	return VL::Vec2(WindowPos.x + ScreenPosition.x * WindowSize.x, WindowPos.y + (1.0f - ScreenPosition.y) * WindowSize.y);
}