#include "PCH/PCH.h"
#include "TextInputDialog.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

namespace Volund
{
	void TextInputDialog::Start(std::function<void(void)> Catch, const std::string& message)
	{
		m_Catch = Catch;
		m_Message = message;
		m_ShouldDraw = true;
		m_Text = "";
	}

	std::string TextInputDialog::GetText()
	{
		return m_Text;
	}

	bool TextInputDialog::Draw()
	{
		if (m_ShouldDraw)
		{
			if (m_Catch == nullptr)
			{
				m_ShouldDraw = false;
				return false;
			}

			const ImVec2 screenSize = ImGui::GetMainViewport()->Size;

			if (ImGui::Begin("###TextInputDialog", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
			{
				const ImVec2 windowSize = ImVec2(250, 100);

				ImGui::SetWindowSize(windowSize);
				ImGui::SetWindowPos(ImVec2((screenSize.x - windowSize.x) / 2, (screenSize.y - windowSize.y) / 2));

				ImGui::SetCursorPosX(windowSize.x / 2 - ImGui::CalcTextSize(m_Message.c_str()).x / 2);
				ImGui::Text(m_Message.c_str());

				ImGui::PushItemWidth(windowSize.x);
				if (ImGui::InputText("###TextInput", &m_Text, ImGuiInputTextFlags_EnterReturnsTrue))
				{
					if (!m_Text.empty())
					{
						m_Catch();
						m_ShouldDraw = false;
						m_Catch = nullptr;
					}
				}
				ImGui::PopItemWidth();

				ImVec2 buttonSize = ImVec2(50, 25);

				ImGui::SetCursorPosX(windowSize.x / 2 - buttonSize.x - 8);
				if (ImGui::Button("Ok", buttonSize))
				{
					if (!m_Text.empty())
					{
						m_Catch();
						m_ShouldDraw = false;
						m_Catch = nullptr;
					}
				}
				ImGui::SameLine();
				if (ImGui::Button("Cancel", buttonSize))
				{
					m_ShouldDraw = false;
					m_Catch = nullptr;
				}
			}

			ImGui::End();

			return true;
		}
		else
		{
			return false;
		}
	}
}