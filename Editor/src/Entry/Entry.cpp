#include "PCH/PCH.h"

#include "Editor/Editor.h"

void Volund::Entry()
{
	auto App = VL::Ref<Editor>(new Editor());

	App->Run();
}