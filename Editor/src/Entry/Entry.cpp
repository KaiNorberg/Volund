#include "PCH/PCH.h"

#include "Editor/Editor.h"

void Volund::Entry()
{
	auto dispatcher = VL::Ref<VL::EventDispatcher>(new VL::EventDispatcher());
	auto app = VL::Ref<Editor>(new Editor());

	dispatcher->Connect(app);
	app->Connect(dispatcher);

	app->Run();
}