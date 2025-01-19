#include "Output.h"

#include "Utils.h"

#include <imgui.h>
#include <thread>

void Output::OnProcedure(const VL::Event& e)
{
	switch (e.type)
	{
	case VOLUND_EVENT_RENDER:
	{
		std::string line;
		while (std::getline(this->m_stream, line)) 
		{
			this->m_lines.push_back(line);
		}
		this->m_stream.clear();

		if (ImGuiListBegin("##outputWindow"))
		{
			for (uint64_t i = 0; i < this->m_lines.size(); i++)
			{
				ImGuiColoredText(this->m_lines[i]);
			}
			ImGuiListEnd();
		}
	}
	break;
	}
}

Output::Output(std::shared_ptr<EditorContext> context)
{
	this->SetName("Output");

	this->m_context = context;

	VOLUND_LOGGER.GetCoreLogger().AddListener(&this->m_stream);
	VOLUND_LOGGER.GetClientLogger().AddListener(&this->m_stream);
}
