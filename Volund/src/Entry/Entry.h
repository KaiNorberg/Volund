#pragma once

namespace Volund
{
	extern Application* CreateApplication();
}

int main(void)
{
	while (true)
	{
		Volund::Application* Application = Volund::CreateApplication();

		Application->Run();

		delete Application;
	}

	return 0;
}