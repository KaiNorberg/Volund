#include "PCH/PCH.h"

#include "EditorLayer/EditorLayer.h"

int main()
{
	Volund::Application* App = new Volund::Application();

	App->AttachLayer(new EditorLayer());

	App->Run();

	delete App;
}