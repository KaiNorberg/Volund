#include "PCH/PCH.h"
#include "TextInputDialog.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

namespace Volund
{
	void TextInputDialog::Start(std::function<void(void)> Catch, const std::string& Message)
	{
		_Catch = Catch;
		_Message = Message;
		_ShouldDraw = true;
		_Text = "";
	}

	std::string TextInputDialog::GetText()
	{
		return _Text;
	}

	bool TextInputDialog::Draw()
	{
		if (_ShouldDraw)
		{
			if (_Catch == nullptr)
			{
				_ShouldDraw = false;
				return false;
			}

			ImVec2 ScreenSize = ImGui::GetMainViewport()->Size;

			if (ImGui::Begin("###TextInputDialog", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
			{
				ImVec2 WindowSize = ImVec2(250, 100);

				ImGui::SetWindowSize(WindowSize);
				ImGui::SetWindowPos(ImVec2((ScreenSize.x - WindowSize.x) / 2, (ScreenSize.y - WindowSize.y) / 2));

				ImGui::SetCursorPosX(WindowSize.x / 2 - ImGui::CalcTextSize(_Message.c_str()).x / 2);
				ImGui::Text(_Message.c_str());

				ImGui::PushItemWidth(WindowSize.x);
				if (ImGui::InputText("###TextInput", &_Text, ImGuiInputTextFlags_EnterReturnsTrue))
				{
					if (!_Text.empty())
					{
						_Catch();
						_ShouldDraw = false;
						_Catch = nullptr;
					}
				}
				ImGui::PopItemWidth();

				ImVec2 ButtonSize = ImVec2(50, 25);

				ImGui::SetCursorPosX(WindowSize.x / 2 - ButtonSize.x - 8);
				if (ImGui::Button("Ok", ButtonSize))
				{
					if (!_Text.empty())
					{
						_Catch();
						_ShouldDraw = false;
						_Catch = nullptr;
					}
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
}