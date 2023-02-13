#include "PCH/PCH.h"

#include "ThreadPool/ThreadPool.h"

#include "Volund.h"

int Main()
{
	VOLUND_PROFILE_FUNCTION();

	//VL::AudioDevice Device(nullptr);
	//VL::AudioContext Context(Device);
	//Context.MakeCurrent();
	//VL::AudioBuffer Buffer("Bell.wav");
	//VL::AudioSource Source;
	//Source.SetBuffer(Buffer);
	//Source.Play();

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