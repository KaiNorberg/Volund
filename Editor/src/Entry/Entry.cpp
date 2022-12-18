#include "PCH/PCH.h"

#include "Editor/Editor.h"

void Volund::Entry()
{
	auto App = VL::Ref<Editor>(new Editor());

	VL::EventDispatcher::ConnectApp(App);

	App->Run();
}