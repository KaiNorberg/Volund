#include "PCH/PCH.h"
#include "TextInputDialog.h"

#include <imgui.h>
#include <imgui_internal.h>

void TextInputDialog::Start(std::function<void(const std::string&)> Catch, const std::string& Message)
{
	_Catch = Catch;
	_Message = Message;
	_ShouldDraw = true;
}

bool TextInputDialog::Update()
{
	if (_ShouldDraw)
	{
		if (_Catch == nullptr)
		{
			_ShouldDraw = false;
			return false;
		}

		ImVec2 ScreenSize = ImGui::GetWindowSize();

		if (ImGui::Begin("###TextInputDialog", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
		{
			ImVec2 WindowSize = ImVec2(250, 125);

			ImGui::SetWindowSize(WindowSize);
			ImGui::SetWindowPos(ImVec2((ScreenSize.x - WindowSize.x) / 2, (ScreenSize.y - WindowSize.y) / 2));

			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::CalcTextSize(_Message.c_str()).x / 2);
			ImGui::Text(_Message.c_str());

			ImGui::PushItemWidth(WindowSize.x);
			static char Text[124];
			if (ImGui::InputText("###", Text, 124, ImGuiInputTextFlags_EnterReturnsTrue))
			{
				_Catch(Text);
				_ShouldDraw = false;
				_Catch = nullptr;
			}
			ImGui::PopItemWidth();

			ImVec2 ButtonSize = ImVec2(50, 25);

			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + WindowSize.x / 2 - ButtonSize.x - 8);
			if (ImGui::Button("Ok", ButtonSize))
			{
				_Catch(Text);
				_ShouldDraw = false;
				_Catch = nullptr;
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ButtonSize))
			{
				_ShouldDraw = false;
				_Catch = nullptr;
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
