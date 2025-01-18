#include "EditorContext.h"

bool EditorContext::IsPaused()
{
	return this->m_Paused;
}

void EditorContext::Enqueue(const VL::Event& e)
{
	this->m_Dispatcher->Enqueue(e);
}

EditorContext::EditorContext(std::shared_ptr<VL::Dispatcher> dispatcher)
{
	this->m_Dispatcher = dispatcher;

	this->State = NULL;

	this->m_Paused = true;
}
