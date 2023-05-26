#include "PCH/PCH.h"

#include "OutputWindow.h"

const char* OutputWindow::GetName()
{
	return "Output";
}

void OutputWindow::LoggerCallback(const std::string& string)
{
	std::unique_lock lock(m_Mutex);

	m_TextList->PushText(string);
}

OutputWindow::OutputWindow(VL::Ref<EditorContext> context)
{
	this->m_Context = context;

	this->AddObject(m_TextList);

	VL::Logger::GetClientLogger().SetCallback(LoggerCallback);
	VL::Logger::GetCoreLogger().SetCallback(LoggerCallback);
}
