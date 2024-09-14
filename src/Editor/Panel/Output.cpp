#include "Output.h"

#include <imgui.h>

void Output::OnProcedure(const VL::Event& e)
{
	switch (e.type)
	{
	case VOLUND_EVENT_RENDER:
	{
		std::vector<std::string> textList;

		if (ImGuiListBegin("##outputWindow"))
		{
			for (const auto& line : VOLUND_LOGGER)
			{
				ImGuiColoredText(line.Text);
			}

			ImGuiListEnd();
		}
	}
	break;
	case EDITOR_EVENT_RESET:
	{

	}
	break;
	}
}

Output::Output(std::shared_ptr<EditorContext> context)
{
	this->SetName("Output");

	this->m_Context = context;
}
