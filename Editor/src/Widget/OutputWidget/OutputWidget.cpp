#include "PCH/PCH.h"

#include "OutputWidget.h"

const char* OutputWidget::GetName()
{
	return "Output";
}

void OutputWidget::OnEvent(VL::Event* E)
{

}

void OutputWidget::OnUpdate(VL::TimeStep TS)
{
	static float TotalTime = 0.0f;

	TotalTime += TS;

	if (ImGui::Begin(this->GetName(), &this->IsActive))
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

	}

	ImGui::End();
}

void OutputWidget::LoggerCallback(const std::string& String)
{
	_Output.push_back(String);
}

OutputWidget::OutputWidget()
{
	VL::Logger::GetClientLogger().SetCallback(LoggerCallback);
	VL::Logger::GetCoreLogger().SetCallback(LoggerCallback);
}
