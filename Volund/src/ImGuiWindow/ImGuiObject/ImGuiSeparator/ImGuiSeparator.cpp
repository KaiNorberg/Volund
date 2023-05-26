#include "PCH/PCH.h"
#include "ImGuiSeparator.h"

#include <imgui.h>

namespace Volund
{
	void ImGuiSeparator::Procedure(const Event& e)
	{
		switch (e.Type)
		{
		case EventType::Render:
		{			
			ImGui::Separator();
		}
		break;
		default:
		{

		}
		break;
		}
	}

	ImGuiSeparator::ImGuiSeparator(const std::string& id)
	{
		this->m_Id = id;
	}
}