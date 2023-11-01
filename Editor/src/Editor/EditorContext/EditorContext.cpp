#include "PCH/PCH.h"
#include "EditorContext.h"

bool EditorContext::IsPaused()
{
	return this->m_Paused;
}

void EditorContext::Enqueue(const VL::Event& e)
{
	this->m_Dispatcher->Enqueue(e);
}

EditorContext::EditorContext(VL::Ref<VL::Dispatcher> dispatcher)
{
	this->m_Dispatcher = dispatcher;

	this->GameState = std::make_shared<VL::GameState>(dispatcher);

	this->m_Paused = true;
}
