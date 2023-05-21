#include "PCH/PCH.h"
#include "ImGuiWindow.h"

#include <imgui.h>

namespace Volund
{
	void ImGuiWindow::Procedure(const Event& e)
	{
		switch (e.Type)
		{
		case EventType::Render:
		{    
			if (this->Position != this->m_PreviousPosition)
			{
				ImGui::SetNextWindowPos(ImVec2(this->Position.x, this->Position.y));
			}
			if (this->Size != this->m_PreviousSize)
			{
				ImGui::SetNextWindowSize(ImVec2(this->Size.x, this->Size.y));
			}

			if (ImGui::Begin(this->GetName(), &this->IsActive))
			{
				ImVec2 windowSize = ImGui::GetWindowSize();
				ImVec2 windowPos = ImGui::GetWindowPos();

				this->Size = Vec2(windowSize.x, windowSize.y);
				this->Position = Vec2(windowPos.x, windowPos.y);
				this->m_PreviousSize = this->Size;
				this->m_PreviousPosition = this->Position;

				for (auto& imGuiObject : this->m_ObjectDrawOrder)
				{
					imGuiObject->Procedure(e);
				}
			}	

			ImGui::End();
		}
		break;
		default:
		{

		}
		break;
		}
	}
}
