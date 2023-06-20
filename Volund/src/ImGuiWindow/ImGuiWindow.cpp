#include "PCH/PCH.h"
#include "ImGuiWindow.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

namespace Volund
{
	bool ImGuiWindow::IsWindowHovered()
	{
		return this->m_IsWindowHovered;
	}

	void ImGuiWindow::SetSize(const Vec2& size)
	{
		this->m_Size = size;
		this->m_SizeChanged = true;
	}

	void ImGuiWindow::SetPosition(const Vec2& position)
	{
		this->m_Position = position;
		this->m_PositionChanged = true;
	}

	void ImGuiWindow::SetName(const std::string& name)
	{
		this->m_Name = name;

		this->SetPosition(this->GetPosition());
		this->SetSize(this->GetSize());
	}

	Vec2 ImGuiWindow::GetSize()
	{
		return this->m_Size;
	}

	Vec2 ImGuiWindow::GetPosition()
	{
		return this->m_Position;
	}

	std::string ImGuiWindow::GetName()
	{
		return this->m_Name;
	}

	std::string ImGuiWindow::GetId()
	{
		return this->m_Name + "##" + this->m_Id;
	}

	void ImGuiWindow::Procedure(const Event& e)
	{
		switch (e.Type)
		{
		case VOLUND_EVENT_TYPE_RENDER:
		{    
			if (ImGui::Begin(this->GetId().c_str(), &this->IsActive))
			{
				if (this->m_PositionChanged)
				{
					ImGui::SetWindowPos(ImVec2(this->m_Position.x, this->m_Position.y));
					this->m_PositionChanged = false;
				}
				if (this->m_SizeChanged)
				{
					ImGui::SetWindowSize(ImVec2(this->m_Size.x, this->m_Size.y));
					this->m_SizeChanged = false;
				}

				ImVec2 windowSize = ImGui::GetWindowSize();
				ImVec2 windowPos = ImGui::GetWindowPos();

				this->m_Size = Vec2(windowSize.x, windowSize.y);
				this->m_Position = Vec2(windowPos.x, windowPos.y);

				this->OnProcedure(e);

				ImVec2 rectMin = ImVec2(this->m_Position.x, this->m_Position.y);
				ImVec2 rectMax = ImVec2(this->m_Position.x + this->m_Size.x, this->m_Position.y + this->m_Size.y);
				this->m_IsWindowHovered = ImGui::IsMouseHoveringRect(rectMin, rectMax);
			}	

			ImGui::End();
		}
		break;
		default:
		{		
			this->OnProcedure(e);
		}
		break;
		}
	}

	void ImGuiWindow::ImGuiStartCombo()
	{
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 100);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 2));
	}

	void ImGuiWindow::ImGuiNextColumn()
	{
		ImGui::NextColumn();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);
	}

	void ImGuiWindow::ImGuiEndCombo()
	{
		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::NextColumn();
	}

	void ImGuiWindow::ImGuiAlign(const std::string& text, float alignment)
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

	bool ImGuiWindow::ImGuiFile(const std::string& name, std::string& out)
	{
		bool outChanged = false;

		ImGuiStartCombo();

		ImGuiColoredText(name.c_str());
		ImGuiNextColumn();

		float LineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 ButtonSize(-FLT_MIN, LineHeight);

		std::string fileName = fs::path(out).filename().string();
		if (fileName.empty())
		{
			fileName = "Drag a file here!";
		}

		ImGui::Button(fileName.c_str(), ButtonSize);

		if (ImGui::BeginDragDropTarget())
		{
			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(VOLUND_IMGUI_FILE);

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

	bool ImGuiWindow::ImGuiString(const std::string& name, std::string& out)
	{
		ImGui::PushID(name.c_str());

		ImGuiStartCombo();

		ImGuiColoredText(name.data());
		ImGuiNextColumn();

		std::string newValue = out;
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

	bool ImGuiWindow::ImGuiInt(const std::string& name, int& value)
	{
		ImGuiStartCombo();

		ImGui::PushID(name.c_str());

		ImGuiColoredText(name.c_str());
		ImGuiNextColumn();

		bool changed = ImGui::DragInt("##", &value);

		ImGui::PopID();

		ImGuiEndCombo();

		return changed;
	}

	bool ImGuiWindow::ImGuiBool(const std::string& name, bool& value)
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

	bool ImGuiWindow::ImGuiFloat(const std::string& name, float& value)
	{
		ImGuiStartCombo();

		ImGui::PushID(name.c_str());

		ImGuiColoredText(name.c_str());
		ImGuiNextColumn();
		bool changed = ImGui::DragFloat("##", &value, 0.1f);

		ImGui::PopID();

		ImGuiEndCombo();

		return changed;
	}

	bool ImGuiWindow::ImGuiDouble(const std::string& name, double& value)
	{
		ImGuiStartCombo();

		ImGui::PushID(name.c_str());

		ImGuiColoredText(name.c_str());
		ImGuiNextColumn();

		bool changed = ImGui::InputDouble("##", &value, 0.1);

		ImGui::PopID();

		ImGuiEndCombo();

		return changed;
	}

	bool ImGuiWindow::ImGuiVec2(const std::string& name, VL::Vec2& value, float speed, float defaultValue)
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

	bool ImGuiWindow::ImGuiVec3(const std::string& name, VL::Vec3& value, float speed, float defaultValue)
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

	bool ImGuiWindow::ImGuiVec4(const std::string& name, VL::Vec4& value, float speed, float defaultValue)
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

	void ImGuiWindow::ImGuiColoredText(const std::string& text)
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

	void ImGuiWindow::ImGuiTextList(const std::string& name, const std::vector<std::string>& textList)
	{
		if (ImGui::BeginListBox(name.c_str(), ImVec2(-FLT_MIN, -FLT_MIN)))
		{
			for (auto& string : textList)
			{
				ImGuiColoredText(string);
			}

			ImGui::SameLine();

			ImGui::SetCursorPosX(ImGui::GetCursorPosX() - ImGui::CalcTextSize("   ").x);

			if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			{
				ImGui::SetScrollHereY(1.0f);
			}

			ImGui::EndListBox();
		}
	}

	void ImGuiWindow::ImGuiDragDropSource(const char* type, const std::string& payload)
	{
		if (ImGui::BeginDragDropSource())
		{
			const char* string = payload.c_str();
			ImGui::Text(string);
			ImGui::SetDragDropPayload(type, string, (std::strlen(string) + 1) * sizeof(char));
			ImGui::EndDragDropSource();
		}
	}

	std::string ImGuiWindow::ImGuiDragDropTarget(const char* type)
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

	VL::Vec2 ImGuiWindow::ToScreenSpace(const VL::Mat4x4& ViewProjMatrix, const VL::Vec3& Position, const VL::Vec2& WindowPos, const VL::Vec2& WindowSize)
	{
		VL::Vec4 ScreenPosition = ViewProjMatrix * VL::Vec4(Position, 1.0f);
		ScreenPosition = (ScreenPosition / ScreenPosition.w) / 2.0f + 0.5f;
		return VL::Vec2(WindowPos.x + ScreenPosition.x * WindowSize.x, WindowPos.y + (1.0f - ScreenPosition.y) * WindowSize.y);
	}

	ImGuiWindow::ImGuiWindow()
	{
		this->m_Id = std::to_string(rand());
	}
}
