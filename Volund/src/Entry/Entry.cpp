#include "PCH/PCH.h"

#include "Core/ThreadPool/ThreadPool.h"

int Main()
{
	VL::ThreadPool::Init();

	VL::Entry();

	VL::ThreadPool::Terminate();

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