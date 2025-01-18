#include "Utils.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>
#include <cstring>

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

void ImGuiAlign(std::string const& text, float alignment)
{
	ImGuiStyle& style = ImGui::GetStyle();

	float size = ImGui::CalcTextSize(text.c_str()).x + style.FramePadding.x * 2.0f;
	float avail = ImGui::GetContentRegionAvail().x;

	float off = (avail - size) * alignment;
	if (off > 0.0f)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
	}
}

bool ImGuiFile(std::string const& name, std::string& out)
{
	bool outChanged = false;

	ImGuiStartCombo();

	ImGuiColoredText(name.c_str());
	ImGuiNextColumn();

	float LineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 ButtonSize(-FLT_MIN, LineHeight);

	std::string fileName = std::filesystem::path(out).filename().string();
	if (fileName.empty())
	{
		fileName = "Drag a file here!";
	}

	ImGui::Button(fileName.c_str(), ButtonSize);

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_DRAG_DROP_FILE);

		if (payload != nullptr)
		{
			const char* path = (const char*)payload->Data;

			out = path;

			outChanged = true;
		}

		ImGui::EndDragDropTarget();
	}

	ImGuiEndCombo();

	return outChanged;
}

bool ImGuiString(std::string const& name, std::string& out)
{
	ImGui::PushID(name.c_str());

	ImGuiStartCombo();

	ImGuiColoredText(name.data());
	ImGuiNextColumn();

	std::string newValue = out;

	ImGui::SetNextItemWidth(-FLT_MIN);
	bool changed = ImGui::InputText("##ImGuiString", &newValue);

	ImGuiEndCombo();

	ImGui::PopID();

	if (changed && ImGui::IsKeyPressed(ImGuiKey_Enter))
	{
		out = newValue;
		return true;
	}
	else
	{
		return false;
	}
}

bool ImGuiInt(std::string const& name, int value)
{
	ImGuiStartCombo();

	ImGui::PushID(name.c_str());

	ImGuiColoredText(name.c_str());
	ImGuiNextColumn();

	ImGui::SetNextItemWidth(-FLT_MIN);
	bool changed = ImGui::DragInt("##", &value);

	ImGui::PopID();

	ImGuiEndCombo();

	return changed;
}

bool ImGuiBool(std::string const& name, bool value)
{
	ImGuiStartCombo();

	ImGui::PushID(name.c_str());

	ImGuiColoredText(name.c_str());
	ImGuiNextColumn();
	bool changed = ImGui::Checkbox("##", &value);

	ImGui::PopID();

	ImGuiEndCombo();

	return changed;
}

bool ImGuiFloat(std::string const& name, float value)
{
	ImGuiStartCombo();

	ImGui::PushID(name.c_str());

	ImGuiColoredText(name.c_str());
	ImGuiNextColumn();

	ImGui::SetNextItemWidth(-FLT_MIN);
	bool changed = ImGui::DragFloat("##", &value, 0.1f);

	ImGui::PopID();

	ImGuiEndCombo();

	return changed;
}

bool ImGuiDouble(std::string const& name, double value)
{
	ImGuiStartCombo();

	ImGui::PushID(name.c_str());

	ImGuiColoredText(name.c_str());
	ImGuiNextColumn();

	ImGui::SetNextItemWidth(-FLT_MIN);
	bool changed = ImGui::InputDouble("##", &value, 0.1);

	ImGui::PopID();

	ImGuiEndCombo();

	return changed;
}

bool ImGuiVec2(std::string const& name, VL::Vec2& value, float speed, float defaultValue)
{
	bool changed = false;

	ImGui::PushID((void*)name.data());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100);

	ImGuiColoredText(name.data());
	ImGui::NextColumn();

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 buttonSize(lineHeight + 3.0f, lineHeight);

	float spacing = 2;

	ImGui::PushMultiItemsWidths(2, ImGui::GetContentRegionAvail().x - (buttonSize.x - spacing) * 2);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, 1));

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
	if (ImGui::Button("X", buttonSize))
	{
		value.x = defaultValue;
		changed = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	if (ImGui::DragFloat("##X", &value.x, speed))
	{
		changed = true;
	}
	ImGui::PopItemWidth();

	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
	if (ImGui::Button("Y", buttonSize))
	{
		value.y = defaultValue;
		changed = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	if (ImGui::DragFloat("##Y", &value.y, speed))
	{
		changed = true;
	}
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();

	ImGui::Columns(1);
	ImGui::PopID();

	return changed;
}

bool ImGuiVec3(std::string const& name, VL::Vec3& value, float speed, float defaultValue)
{
	bool changed = false;

	ImGui::PushID((void*)name.data());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100);

	ImGuiColoredText(name.data());
	ImGui::NextColumn();

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 buttonSize(lineHeight + 3.0f, lineHeight);

	float spacing = 2;

	ImGui::PushMultiItemsWidths(3, ImGui::GetContentRegionAvail().x - (buttonSize.x - spacing) * 3);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, 1));

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
	if (ImGui::Button("X", buttonSize))
	{
		value.x = defaultValue;
		changed = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	if (ImGui::DragFloat("##X", &value.x, speed))
	{
		changed = true;
	}
	ImGui::PopItemWidth();

	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
	if (ImGui::Button("Y", buttonSize))
	{
		value.y = defaultValue;
		changed = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	if (ImGui::DragFloat("##Y", &value.y, speed))
	{
		changed = true;
	}
	ImGui::PopItemWidth();

	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
	if (ImGui::Button("Z", buttonSize))
	{
		value.z = defaultValue;
		changed = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	if (ImGui::DragFloat("##Z", &value.z, speed))
	{
		changed = true;
	}
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();

	ImGui::Columns(1);
	ImGui::PopID();

	return changed;
}

bool ImGuiVec4(std::string const& name, VL::Vec4& value, float speed, float defaultValue)
{
	bool changed = false;

	ImGui::PushID((void*)name.data());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100);

	ImGuiColoredText(name.data());
	ImGui::NextColumn();

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 buttonSize(lineHeight + 3.0f, lineHeight);

	float spacing = 2;

	ImGui::PushMultiItemsWidths(4, ImGui::GetContentRegionAvail().x - (buttonSize.x - spacing) * 4);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, 1));

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
	if (ImGui::Button("X", buttonSize))
	{
		value.x = defaultValue;
		changed = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	if (ImGui::DragFloat("##X", &value.x, speed))
	{
		changed = true;
	}
	ImGui::PopItemWidth();

	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
	if (ImGui::Button("Y", buttonSize))
	{
		value.y = defaultValue;
		changed = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	if (ImGui::DragFloat("##Y", &value.y, speed))
	{
		changed = true;
	}
	ImGui::PopItemWidth();

	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
	if (ImGui::Button("Z", buttonSize))
	{
		value.z = defaultValue;
		changed = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	if (ImGui::DragFloat("##Z", &value.z, speed))
	{
		changed = true;
	}
	ImGui::PopItemWidth();

	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
	if (ImGui::Button("W", buttonSize))
	{
		value.w = defaultValue;
		changed = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	if (ImGui::DragFloat("##W", &value.w, speed))
	{
		changed = true;
	}
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();

	ImGui::Columns(1);
	ImGui::PopID();

	return changed;
}

void ImGuiColoredText(std::string const& text)
{
	ImGuiStyle* style = &ImGui::GetStyle();

	const ImVec4 oldTextColor = style->Colors[ImGuiCol_Text];

	size_t prevIndex = 0;
	while (true)
	{
		auto newIndex = text.find_first_of('\033', prevIndex);
		if (newIndex != std::string::npos)
		{
			if (prevIndex - newIndex != 0)
			{
				ImGui::Text(text.substr(prevIndex, newIndex - prevIndex).c_str());
				ImGui::SameLine();
			}

			prevIndex = newIndex + 5;

			std::string_view colorCode = std::string_view(text.begin() + newIndex, text.begin() + newIndex + 5);

			if (colorCode == VOLUND_LOGGERCOLOR_BLACK)
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
			}
			else if (colorCode == VOLUND_LOGGERCOLOR_RED)
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.8f, 0.1f, 0.1f, 1.00f);
			}
			else if (colorCode == VOLUND_LOGGERCOLOR_GREEN)
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.42f * 1.5f, 0.52f * 1.5f, 0.36f * 1.5f, 1.00f);
			}
			else if (colorCode == VOLUND_LOGGERCOLOR_YELLOW)
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.8f, 0.6f, 0.0f, 1.00f);
			}
			else if (colorCode == VOLUND_LOGGERCOLOR_BLUE)
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.36f, 0.68f, 0.93f, 1.00f);
			}
			else if (colorCode == VOLUND_LOGGERCOLOR_MAGENTA)
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.55f, 0.1f, 0.5f, 1.00f);
			}
			else if (colorCode == VOLUND_LOGGERCOLOR_CYAN)
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.1f, 0.6f, 0.9f, 1.00f);
			}
			else if (colorCode == VOLUND_LOGGERCOLOR_WHITE)
			{
				style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
			}
		}
		else
		{
			ImGui::Text(text.substr(prevIndex).c_str());
			break;
		}
	}

	style->Colors[ImGuiCol_Text] = oldTextColor;
}

bool ImGuiListBegin(std::string const& name)
{
	return ImGui::BeginListBox(name.c_str(), ImVec2(-FLT_MIN, -FLT_MIN));
}

void ImGuiListEnd()
{
	ImGui::SameLine();

	ImGui::SetCursorPosX(ImGui::GetCursorPosX() - ImGui::CalcTextSize("   ").x);

	if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
	{
		ImGui::SetScrollHereY(1.0f);
	}

	ImGui::EndListBox();
}

void ImGuiDragDropSource(const char* type, std::string const& payload)
{
	if (ImGui::BeginDragDropSource())
	{
		const char* string = payload.c_str();
		ImGui::Text(string);
		ImGui::SetDragDropPayload(type, string, (std::strlen(string) + 1) * sizeof(char));
		ImGui::EndDragDropSource();
	}
}

std::string ImGuiDragDropTarget(const char* type)
{
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(type);
		if (payload != nullptr)
		{
			std::string out = (const char*)payload->Data;
			ImGui::EndDragDropTarget();
			return out;
		}
		else
		{
			ImGui::EndDragDropTarget();
		}
	}

	return std::string();
}

VL::Vec2 ToScreenSpace(const VL::Mat4x4& ViewProjMatrix, const VL::Vec3& Position, const VL::Vec2& WindowPos, const VL::Vec2& WindowSize)
{
	VL::Vec4 ScreenPosition = ViewProjMatrix * VL::Vec4(Position.x, Position.y, Position.z, 1.0f);
	ScreenPosition = (ScreenPosition / ScreenPosition.w) / 2.0f + 0.5f;
	return VL::Vec2(WindowPos.x + ScreenPosition.x * WindowSize.x, WindowPos.y + (1.0f - ScreenPosition.y) * WindowSize.y);
}
