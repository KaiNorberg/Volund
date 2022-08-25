#include "PCH/PCH.h"

#include "Engine.h"

#include "EngineLayer.h"

namespace Volund
{
	Engine::Engine()
	{
		this->AttachLayer(new EngineLayer());
	}
}

Volund::Application* Volund::CreateApplication()
{
	return new Engine();
}