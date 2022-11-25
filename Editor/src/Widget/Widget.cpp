#include "PCH/PCH.h"

#include "Widget.h"

void Widget::DrawText(const std::string& String)
{
	ImGuiStyle* Style = &ImGui::GetStyle();

	ImVec4 OldTextColor = Style->Colors[ImGuiCol_Text];

	std::string OutputString;
	OutputString.reserve(String.size());
	for (int i = 0; i < String.size(); i++)
	{
		if (i - String.size() > 5 && String[i] == '\033'
			&& String[i + 1] == '[' && String[i + 2] == '3' && String[i + 4] == 'm')
		{
			if (!OutputString.empty())
			{
				ImGui::Text(OutputString.c_str());
				ImGui::SameLine();
				OutputString.clear();
			}

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
				Style->Colors[ImGuiCol_Text] = ImVec4(0.42f * 1.5f, 0.52f * 1.5f, 0.36f * 1.5f, 1.00f);
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
			OutputString.push_back(String[i]);
		}
	}

	if (!OutputString.empty())
	{
		ImGui::Text(OutputString.c_str());
	}

	Style->Colors[ImGuiCol_Text] = OldTextColor;
}