#include "PCH/PCH.h"
#include "ImGuiTextList.h"

#include <imgui.h>

namespace Volund
{
	uint64_t ImGuiTextList::GetSize()
	{
		return this->m_TextList.size();
	}

	void ImGuiTextList::PushText(const std::string& text)
	{
		this->m_TextList.push_back(text);
	}

	void ImGuiTextList::SetText(uint32_t i, const std::string& text)
	{
		if (i < this->m_TextList.size())
		{
			this->m_TextList[i] = text;
		}
	}

	std::string ImGuiTextList::GetText(uint32_t i)
	{
		if (i < this->m_TextList.size())
		{
			return this->m_TextList[i];
		}
		else
		{
			return std::string();
		}
	}

	void ImGuiTextList::Procedure(const Event& e)
	{
		switch (e.Type)
		{
		case EventType::Render:
		{		
			if (ImGui::BeginListBox(this->m_Id.c_str(), ImVec2(-FLT_MIN, -FLT_MIN)))
			{
				for (auto& string : m_TextList)
				{
					ImGuiColoredText(string);
				}

				ImGui::SameLine();

				ImGui::SetCursorPosX(ImGui::GetCursorPosX() - ImGui::CalcTextSize("   ").x);

				if (static_cast<int>(m_TotalTime * 2) % 2 == 0)
				{
					ImGui::Text("|");
				}
				else
				{
					ImGui::Text(" ");
				}

				if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
				{
					ImGui::SetScrollHereY(1.0f);
				}

				ImGui::EndListBox();
			}
		}
		break;
		case VL::EventType::Update:
		{
			float timeStep = VOLUND_EVENT_UPDATE_GET_TIMESTEP(e);

			this->m_TotalTime += timeStep;
		}
		break;
		default:
		{

		}
		break;
		}
	}

	ImGuiTextList::ImGuiTextList(const std::string& id)
	{
		this->m_Id = id;
	}
}