#include "PCH/PCH.h"
#include "ImGuiText.h"

#include <imgui.h>

namespace Volund
{
	void ImGuiText::Procedure(const Event& e)
	{
		switch (e.Type)
		{
		case EventType::Render:
		{
			ImGui::Text(this->m_Id.c_str());
		}
		break;
		default:
		{

		}
		break;
		}
	}

	ImGuiText::ImGuiText(const std::string& id)
	{
		this->m_Id = id;
	}
}