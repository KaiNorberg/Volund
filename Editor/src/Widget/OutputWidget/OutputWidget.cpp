#include "PCH/PCH.h"

#include "OutputWidget.h"

const char* OutputWidget::GetName()
{
	return "Output";
}

void OutputWidget::OnUpdate(VL::TimeStep TS)
{
	TotalTime += (float)TS;
}

void OutputWidget::OnRender()
{
	std::unique_lock Lock(_Mutex);

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
	std::unique_lock Lock(_Mutex);

	if (_Output.size() > 25)
	{
		_Output.erase(_Output.begin());
	}

	_Output.push_back(String);
}

OutputWidget::OutputWidget(VL::Application* App)
{
	this->_App = App;

	VL::Logger::GetClientLogger().SetCallback(LoggerCallback);
	VL::Logger::GetCoreLogger().SetCallback(LoggerCallback);
}
