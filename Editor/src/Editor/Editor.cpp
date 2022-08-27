#include "PCH/PCH.h"

#include "Editor.h"

namespace Volund
{
	Editor::Editor()
	{
		this->AttachLayer(new GameLayer());
	}
}

Volund::Application* Volund::CreateApplication()
{
	return new Editor();
}