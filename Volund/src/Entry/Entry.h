#pragma once

namespace Volund
{		
	//Needs to be defined by the client.
	extern Application* CreateApplication();
}

int main(int argc, char* argv)
{
	Volund::Application* Application = Volund::CreateApplication();

	Application->Run();

	delete Application;

	return 0;
} 