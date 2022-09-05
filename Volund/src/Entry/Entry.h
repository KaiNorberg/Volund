#pragma once

namespace Volund
{		
	/// <summary>
	/// This function needs to be defined by a client.
	/// It should return a pointer that inherits from the Application class, deletion of the pointer will be handled by Volund.
	/// </summary>
	extern Application* CreateApplication();

	extern bool ShouldRun;
}

int main(int argc, char* argv)
{
	while (Volund::ShouldRun)
	{
		Volund::Application* Application = Volund::CreateApplication();

		Application->Run();

		delete Application;
	}

	return 0;
} 