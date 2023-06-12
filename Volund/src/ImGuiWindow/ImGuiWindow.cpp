#include "PCH/PCH.h"
#include "ImGuiWindow.h"

#include <imgui.h>

namespace Volund
{
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
		this->OnProcedure(e);

		switch (e.Type)
		{
		case EventType::Render:
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

				for (auto& imGuiObject : this->m_ObjectDrawOrder)
				{
					if (imGuiObject->IsActive)
					{
						ImGui::PushID(imGuiObject->GetId().c_str());
						imGuiObject->Procedure(e);
						ImGui::PopID();
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

	ImGuiWindow::ImGuiWindow()
	{
		this->m_Id = std::to_string(rand());
	}
}
