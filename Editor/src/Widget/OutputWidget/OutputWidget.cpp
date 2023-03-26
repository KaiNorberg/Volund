#include "PCH/PCH.h"

#include "OutputWidget.h"

const char* OutputWidget::GetName()
{
	return "Output";
}

void OutputWidget::OnUpdate(const VL::TimeStep ts)
{
	m_TotalTime += (float)ts;
}

void OutputWidget::OnRender()
{
	std::unique_lock lock(m_Mutex);

	if (ImGui::Begin(this->GetName(), &this->IsActive))
	{
		if (ImGui::BeginListBox("###OutputTextbox", ImVec2(-FLT_MIN, -FLT_MIN)))
		{
			for (auto& string : m_Output)
			{
				DrawText(string);
			}

			ImGui::SameLine();

			ImGui::SetCursorPosX(ImGui::GetCursorPosX() - ImGui::CalcTextSize("   ").x);

			if (static_cast<int>(m_TotalTime * 2) % 2 == 0)
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

void OutputWidget::LoggerCallback(const std::string& string)
{
	std::unique_lock lock(m_Mutex);

	if (m_Output.size() > 25)
	{
		m_Output.erase(m_Output.begin());
	}

	m_Output.push_back(string);
}

OutputWidget::OutputWidget(VL::Application* app)
{
	this->m_App = app;

	VL::Logger::GetClientLogger().SetCallback(LoggerCallback);
	VL::Logger::GetCoreLogger().SetCallback(LoggerCallback);
}
