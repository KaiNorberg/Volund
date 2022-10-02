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
	ImGuiStyle* Style = &ImGui::GetStyle();

	if (ImGui::Begin("Output", &this->_IsActive))
	{
		ImGui::PushTextWrapPos();

		for (auto& String : _Output)
		{
			std::string FinalString;
			FinalString.reserve(String.size());
			for (int i = 0; i < String.size(); i++)
			{
				if (i - String.size() > 5 && String[i] == '\033' 
					&& String[i + 1] == '[' && String[i + 2] == '3' && String[i + 4] == 'm')
				{
					ImGui::Text(FinalString.c_str());
					ImGui::SameLine();
					FinalString.clear();

					switch (String[i + 3])
					{
					case VOLUND_LOGGERCOLOR_BLACK[3]:
					{
						Style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);					
					}
					break;
					case VOLUND_LOGGERCOLOR_RED[3]:
					{
						Style->Colors[ImGuiCol_Text] = ImVec4(0.8f, 0.1f, 0.1f, 1.00f);
					}
					break;
					case VOLUND_LOGGERCOLOR_GREEN[3]:
					{							
						Style->Colors[ImGuiCol_Text] = ImVec4(0.42f, 0.52f, 0.36f, 1.00f);
					}
					break;
					case VOLUND_LOGGERCOLOR_YELLOW[3]:
					{						
						Style->Colors[ImGuiCol_Text] = ImVec4(0.8f, 0.6f, 0.0f, 1.00f);
					}
					break;
					case VOLUND_LOGGERCOLOR_BLUE[3]:
					{							
						Style->Colors[ImGuiCol_Text] = ImVec4(0.36f, 0.68f, 0.93f, 1.00f);
					}
					break;
					case VOLUND_LOGGERCOLOR_MAGENTA[3]:
					{
						Style->Colors[ImGuiCol_Text] = ImVec4(0.55f, 0.1f, 0.5f, 1.00f);
					}
					break;
					case VOLUND_LOGGERCOLOR_CYAN[3]:
					{
						Style->Colors[ImGuiCol_Text] = ImVec4(0.1f, 0.6f, 0.9f, 1.00f);
					}
					break;
					case VOLUND_LOGGERCOLOR_WHITE[3]:
					{
						Style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
					}
					break;
					}
					i += 4;				
				}
				else
				{
					FinalString.push_back(String[i]);
				}
			}
			ImGui::Text(FinalString.c_str());
		}

		if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		{
			ImGui::SetScrollHereY(1.0f);
		}

		ImGui::PopTextWrapPos();

		Style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

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
