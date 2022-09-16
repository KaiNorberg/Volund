#include "PCH/PCH.h"

#include "Editor/Editor.h"

int Main()
{
	Editor* App = new Editor();

	App->Run();

	delete App;

	return EXIT_SUCCESS;
}

#ifdef VOLUND_DIST

#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	return Main();
}

#else

int main()
{
	return Main();
}

#endif