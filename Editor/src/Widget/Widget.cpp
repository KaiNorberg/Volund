#include "PCH/PCH.h"

#include "Widget.h"

void Widget::DrawText(const std::string& string)
{
	ImGuiStyle* style = &ImGui::GetStyle();

	const ImVec4 oldTextColor = style->Colors[ImGuiCol_Text];

	std::string outputString;
	outputString.reserve(string.size());
	for (int i = 0; i < string.size(); i++)
	{
		if (i - string.size() > 5 && string[i] == '\033'
			&& string[i + 1] == '[' && string[i + 2] == '3' && string[i + 4] == 'm')
		{
			if (!outputString.empty())
			{
				ImGui::Text(outputString.c_str());
				ImGui::SameLine();
				outputString.clear();
			}

			switch (string[i + 3])
			{
			case VOLUND_LOGGERCOLOR_BLACK[3]:
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
			}
			break;
			case VOLUND_LOGGERCOLOR_RED[3]:
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.8f, 0.1f, 0.1f, 1.00f);
			}
			break;
			case VOLUND_LOGGERCOLOR_GREEN[3]:
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.42f * 1.5f, 0.52f * 1.5f, 0.36f * 1.5f, 1.00f);
			}
			break;
			case VOLUND_LOGGERCOLOR_YELLOW[3]:
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.8f, 0.6f, 0.0f, 1.00f);
			}
			break;
			case VOLUND_LOGGERCOLOR_BLUE[3]:
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.36f, 0.68f, 0.93f, 1.00f);
			}
			break;
			case VOLUND_LOGGERCOLOR_MAGENTA[3]:
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.55f, 0.1f, 0.5f, 1.00f);
			}
			break;
			case VOLUND_LOGGERCOLOR_CYAN[3]:
			{
				style->Colors[ImGuiCol_Text] = ImVec4(0.1f, 0.6f, 0.9f, 1.00f);
			}
			break;
			case VOLUND_LOGGERCOLOR_WHITE[3]:
			{
				style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
			}
			break;
			}
			i += 4;
		}
		else
		{
			outputString.push_back(string[i]);
		}
	}

	if (!outputString.empty())
	{
		ImGui::Text(outputString.c_str());
	}

	style->Colors[ImGuiCol_Text] = oldTextColor;
}