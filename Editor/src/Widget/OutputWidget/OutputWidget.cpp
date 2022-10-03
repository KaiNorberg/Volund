#include "PCH/PCH.h"
#include "OutputWidget.h"

#include "Editor/Editor.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

const char* OutputWidget::GetName()
{
	return "Output";
}

void OutputWidget::Draw(VL::TimeStep TS)
{
	static float TotalTime = 0.0f;

	TotalTime += TS;

	if (ImGui::Begin("Output", &this->_IsActive))
	{
		if (ImGui::BeginListBox("###OutputTextbox", ImVec2(-FLT_MIN, -FLT_MIN)))
		{
			for (auto& String : _Output)
			{
				DrawText(String);
			}

			ImGui::SameLine();

			ImGui::SetCursorPosX(ImGui::GetCursorPosX() - ImGui::CalcTextSize("   ").x);

			if ((int)(TotalTime * 2) % 2 == 0)
			{
				ImGui::Text("|");
			}
			else
			{
				ImGui::Text(" ");
			}

			if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			{
				ImGui::SetScrollHereY(1.0f);
			}

			ImGui::EndListBox();
		}

		ImGui::End();
	}
}

void OutputWidget::LoggerCallback(const std::string& String)
{
	_Output.push_back(String);
}

OutputWidget::OutputWidget(Editor* editor, bool Active) 
	: Widget(editor, Active)
{
	VL::Logger::GetClientLogger().SetCallback(LoggerCallback);
	VL::Logger::GetCoreLogger().SetCallback(LoggerCallback);
}
