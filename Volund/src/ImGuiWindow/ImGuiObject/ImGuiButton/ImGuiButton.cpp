#include "PCH/PCH.h"
#include "ImGuiButton.h"

#include <imgui.h>

namespace Volund
{
	void ImGuiButton::SetText(const std::string& text)
	{
		this->m_Text = text;
	}

	std::string ImGuiButton::GetText()
	{
		return this->m_Text;
	}

	void ImGuiButton::SetCallback(std::function<void(ImGuiButton*)> callback)
	{
		this->m_Callback = callback;
	}

	std::function<void(ImGuiButton*)> ImGuiButton::GetCallback()
	{
		return this->m_Callback;
	}

	void ImGuiButton::Procedure(const Event& e)
	{
		switch (e.Type)
		{
		case EventType::Render:
		{   
			if (Alignment != 0.0f)
			{
				ImGuiStyle& style = ImGui::GetStyle();

				float size = ImGui::CalcTextSize(this->m_Text.c_str()).x + style.FramePadding.x * 2.0f;
				float avail = ImGui::GetContentRegionAvail().x;

				float off = (avail - size) * Alignment;
				if (off > 0.0f)
				{
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
				}
			}

			if (ImGui::Button(this->m_Text.c_str()))
			{
				if (this->m_Callback != nullptr)
				{
					this->m_Callback(this);
				}
			}
		}
		break;
		default:
		{

		}
		break;
		}
	}

	ImGuiButton::ImGuiButton(const std::string& text, std::function<void(ImGuiButton*)> callback, float alignment)
	{
		this->m_Text = text;
		this->m_Callback = callback;
		this->Alignment = alignment;
	}
}