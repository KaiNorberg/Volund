#include "PCH/PCH.h"

#include "Editor/Editor.h"

int Main()
{
	VOLUND_PROFILE_FUNCTION();

	auto app = VL::Ref<Editor>(new Editor());

	app->Run();

	return EXIT_SUCCESS;
}

#if defined(VOLUND_DIST) && defined(_WIN32)

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