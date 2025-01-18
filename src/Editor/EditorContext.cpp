#include "EditorContext.h"

bool EditorContext::IsPaused()
{
	return this->m_paused;
}

void EditorContext::Enqueue(const VL::Event& e)
{
	this->m_dispatcher->Enqueue(e);
}

EditorContext::EditorContext(std::shared_ptr<VL::Dispatcher> dispatcher) : m_dispatcher{dispatcher}
{
	this->state = std::make_shared<VL::LuaState>(".");
}
