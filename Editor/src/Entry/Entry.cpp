#include "PCH/PCH.h"

#include "Editor/Editor.h"

void Volund::Entry()
{
	auto app = VL::Ref<Editor>(new Editor());

	app->Run();
}