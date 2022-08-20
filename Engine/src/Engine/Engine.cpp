#include "Volund.h"

#include "Engine.h"

namespace Volund
{
	class Engine : public Volund::Application
	{

	};

}

Volund::Application* Volund::CreateApplication()
{
	return new Engine();
}