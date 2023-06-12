#include "PCH/PCH.h"
#include "ImGuiText.h"

#include <imgui.h>

namespace Volund
{
	void ImGuiText::SetText(const std::string& text)
	{
		this->m_Text = text;
	}

	std::string ImGuiText::GetText()
	{
		return this->m_Text;
	}

	void ImGuiText::Procedure(const Event& e)
	{
		switch (e.Type)
		{
		case EventType::Render:
		{			
			ImGuiColoredText(this->m_Text.c_str());
		}
		break;
		default:
		{

		}
		break;
		}
	}

	ImGuiText::ImGuiText(const std::string& text)
	{
		this->m_Text = text;
	}
}