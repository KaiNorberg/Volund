#include "PCH/PCH.h"

#include "OutputWindow.h"

void OutputWindow::LoggerCallback(const std::string& string)
{
	std::unique_lock lock(m_Mutex);

	m_TextList.push_back(string);
}

void OutputWindow::OnProcedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VOLUND_EVENT_TYPE_RENDER:
	{
		ImGuiTextList("##outputWindow", m_TextList);
	}
	break;
	case EDITOR_EVENT_TYPE_NEW_SCENE:
	{
		m_TextList.clear();
	}
	break;
	}
}

OutputWindow::OutputWindow(VL::Ref<EditorContext> context)
{
	this->SetName("Output");

	this->m_Context = context;

	VL::Logger::GetClientLogger().SetCallback(LoggerCallback);
	VL::Logger::GetCoreLogger().SetCallback(LoggerCallback);
}
