#include "EditorContext.hpp"

bool EditorContext::IsPaused()
{
	return this->m_paused;
}

void EditorContext::Enqueue(const VL::Event& e)
{
	this->m_dispatcher->Enqueue(e);
}

EditorContext::EditorContext(std::shared_ptr<VL::Dispatcher> dispatcher, std::shared_ptr<VL::Window> window)
{
	this->m_dispatcher = dispatcher;
	this->window = window;
	this->state = std::make_shared<VL::LuaState>(".");
}
