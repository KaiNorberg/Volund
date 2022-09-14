#include "PCH/PCH.h"

#include "Editor/Editor.h"

int main()
{
	Editor* App = new Editor();

	App->Run();

	delete App;
}