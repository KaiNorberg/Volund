#include "PCH/PCH.h"

#include "ThreadPool/ThreadPool.h"

int Main()
{
	VL::Entry();

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