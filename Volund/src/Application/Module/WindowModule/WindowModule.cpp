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
		this->Window->Update();
		this->Context->Flush();
	}

	void WindowModule::OnAttach(Application* App)
	{
		this->Window = VL::Ref<VL::Window>(new VL::Window(App->GetEventDispatcher(), 1980, 1080, false));

		this->Window->SetTitle("Volund Editor");
		this->Window->SetCursorMode(VL::CursorMode::NORMAL);
		this->Window->SetFocus();

		this->Context = VL::Context::Create(this->Window);
		this->Context->SetVSync(true);
		this->Context->MakeCurrent();
	}

	void WindowModule::OnDestroy()
	{

	}
	
	WindowModule::WindowModule()
	{

	}
}