#include "PCH/PCH.h"
#include "WindowModule.h"

#include "Application/Application.h"

namespace Volund
{
	Ref<Window> WindowModule::GetWindow()
	{
		return this->_Window;
	}

	void WindowModule::OnAttach(Application* App)
	{
		this->_Window = std::make_shared<Window>(App->GetEventDispatcher(), 1980, 1080, false);

		this->_Window->SetTitle("Volund");
		this->_Window->SetFocus();

		this->_Window->Show();
	}

	void WindowModule::OnDetach()
	{
	}

	void WindowModule::Procedure(const Event& E)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (E.Type)
		{
		case EventType::RENDER:
		{
			this->_Window->Update();
			this->_Window->Flush();
		}
		break;
		default:
		{

		}
		break;
		}
	}
	
	WindowModule::WindowModule()
	{

	}
}