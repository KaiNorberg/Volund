#include "PCH/PCH.h"
#include "WindowModule.h"

#include "Application/Application.h"

namespace Volund
{
	Ref<Window> WindowModule::GetWindow()
	{
		return this->_Window;
	}

	void WindowModule::OnEvent(Event* E)
	{

	}

	void WindowModule::OnUpdate(TimeStep TS)
	{

	}

	void WindowModule::OnRender()
	{
		this->_Window->Update();
		this->_Window->Flush();
	}

	void WindowModule::OnAttach(Application* App)
	{
		this->_Window = std::make_shared<Window>(App->GetEventDispatcher(), 1980, 1080, false);

		this->_Window->SetTitle("Volund");
		this->_Window->SetFocus();

		this->_Window->Show();
	}

	void WindowModule::OnDestroy()
	{

	}
	
	WindowModule::WindowModule()
	{

	}
}