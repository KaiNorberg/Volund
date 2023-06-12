#include "PCH/PCH.h"
#include "ImGuiTabBar.h"

#include <imgui.h>

namespace Volund
{
	void ImGuiTabBar::Procedure(const Event& e)
	{
		switch (e.Type)
		{
		case EventType::Render:
		{			
			if (ImGui::BeginTabBar(this->GetId().c_str(), ImGuiTabBarFlags_Reorderable))
			{
				for (const auto& tab : this->m_Tabs)
				{
					if (ImGui::BeginTabItem(tab.Name.c_str()))
					{
						tab.Object->Procedure(e);

						ImGui::EndTabItem();
					}
				}
			}
			ImGui::EndTabBar();

			break;
		}
		break;
		default:
		{
			for (const auto& tab : m_Tabs)
			{
				tab.Object->Procedure(e);
			}
		}
		break;
		}
	}
}