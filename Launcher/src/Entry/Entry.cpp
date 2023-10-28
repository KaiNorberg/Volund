#include "PCH/PCH.h"

#include "Launcher/Launcher.h"

int Main()
{
	VOLUND_PROFILE_FUNCTION();

	auto app = VL::Ref<Launcher>(new Launcher());

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