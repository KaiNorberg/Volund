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
		this->Context->Flush();
		Window::SwapBuffers();
	}

	void WindowModule::OnAttach(Application* App)
	{
		Window::Create(App->GetEventDispatcher(), 1980, 1080, false);

		Window::SetTitle("Volund Editor");
		Window::SetCursorMode(VL::CursorMode::NORMAL);
		Window::SetFocus();

		this->Context = VL::Context::Create(Window::GetDeviceContext());
		this->Context->SetVSync(true);
		this->Context->MakeCurrent();

		Window::Show();
	}

	void WindowModule::OnDestroy()
	{

	}
	
	WindowModule::WindowModule()
	{

	}
}