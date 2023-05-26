#include "PCH/PCH.h"
#include "ImGuiWindow.h"

#include <imgui.h>

namespace Volund
{
	void ImGuiWindow::SetSize(const Vec2& size)
	{
		this->m_Size = size;
		ImGui::SetWindowSize(this->GetName(), ImVec2(size.x, size.y));
	}

	void ImGuiWindow::SetPosition(const Vec2& position)
	{
		this->m_Position = position;
		ImGui::SetWindowPos(this->GetName(), ImVec2(position.x, position.y));
	}

	Vec2 ImGuiWindow::GetSize()
	{
		return this->m_Size;
	}

	Vec2 ImGuiWindow::GetPosition()
	{
		return this->m_Position;
	}

	void ImGuiWindow::Procedure(const Event& e)
	{
		this->OnProcedure(e);

		switch (e.Type)
		{
		case EventType::Render:
		{    
			if (ImGui::Begin(this->GetName(), &this->IsActive))
			{
				ImVec2 windowSize = ImGui::GetWindowSize();
				ImVec2 windowPos = ImGui::GetWindowPos();

				this->m_Size = Vec2(windowSize.x, windowSize.y);
				this->m_Position = Vec2(windowPos.x, windowPos.y);

				for (auto& imGuiObject : this->m_ObjectDrawOrder)
				{
					if (imGuiObject->IsActive)
					{
						imGuiObject->Procedure(e);
					}
				}
			}	

			ImGui::End();
		}
		break;
		default:
		{
			for (auto& imGuiObject : this->m_ObjectDrawOrder)
			{
				imGuiObject->Procedure(e);
			}
		}
		break;
		}
	}
}
