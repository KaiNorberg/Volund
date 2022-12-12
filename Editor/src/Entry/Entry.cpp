#include "PCH/PCH.h"

#include "Editor/Editor.h"

void Volund::Entry()
{
	Editor* App = new Editor();
	App->Run();
	delete App;
}