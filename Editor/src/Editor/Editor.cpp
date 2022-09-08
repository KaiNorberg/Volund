#include "PCH/PCH.h"

#include "Editor.h"

#include "EditorLayer/EditorLayer.h"

Editor::Editor()
{
	this->AttachLayer(new EditorLayer());
}

int main()
{
	Editor* App = new Editor();

	App->Run();

	delete App;
}