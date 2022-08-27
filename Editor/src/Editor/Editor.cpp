#include "PCH/PCH.h"

#include "Editor.h"

Editor::Editor()
{
	this->AttachLayer(new Volund::GameLayer());
}


Volund::Application* Volund::CreateApplication()
{
	return new Editor();
}