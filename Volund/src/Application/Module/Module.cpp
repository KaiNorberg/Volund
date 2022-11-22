#include "PCH/PCH.h"
#include "Module.h"

namespace Volund
{
	void Module::OnEvent(Event* E)
	{

	}

	void Module::OnUpdate(TimeStep TS)
	{

	}

	void Module::OnAttach(Application* App)
	{

	}

	void Module::OnDestroy()
	{

	}

	Module::Module()
	{

	}

	Module::~Module()
	{
		this->OnDestroy();
	}
}