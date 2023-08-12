#include "PCH/PCH.h"

#include "OutputWindow.h"

void OutputWindow::OnProcedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VOLUND_EVENT_TYPE_RENDER:
	{
		std::vector<std::string> textList;
	
		ImGuiTextList("##outputWindow", textList);
	}
	break;
	case EDITOR_EVENT_TYPE_NEW_SCENE:
	{

	}
	break;
	}
}

OutputWindow::OutputWindow(VL::Ref<EditorContext> context)
{
	this->SetName("Output");

	this->m_Context = context;
}
