#include "PCH/PCH.h"
#include "WindowModule.h"

#include "Application/Application.h"

namespace Volund
{
	void WindowModule::OnEvent(Event* E)
	{

	}

	void WindowModule::OnUpdate(TimeStep TS)
	{
		Window::Update();
		Window::Flush();
	}

	void WindowModule::OnAttach(Application* App)
	{
		Window::Create(App->GetEventDispatcher(), 1980, 1080, false);

		Window::SetTitle("Volund Editor");
		Window::SetFocus();

		Window::Show();
	}

	void WindowModule::OnDestroy()
	{

	}
	
	WindowModule::WindowModule()
	{

	}
}