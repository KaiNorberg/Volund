#include "PCH/PCH.h"

#include "OutputWindow.h"


void OutputWindow::LoggerCallback(const std::string& string)
{
	std::unique_lock lock(m_Mutex);

	m_TextList->PushText(string);
}

OutputWindow::OutputWindow(VL::Ref<EditorContext> context)
{
	this->SetName("Output");

	this->m_Context = context;

	this->PushObject(m_TextList);

	VL::Logger::GetClientLogger().SetCallback(LoggerCallback);
	VL::Logger::GetCoreLogger().SetCallback(LoggerCallback);
}
