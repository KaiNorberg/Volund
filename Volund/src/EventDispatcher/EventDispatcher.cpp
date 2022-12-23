#include "PCH/PCH.h"

#include "EventDispatcher.h"
#include "Input/Input.h"

#include "Application/Application.h"

namespace Volund
{
	void EventDispatcher::Dispatch(const Event& E)
	{
		VOLUND_PROFILE_FUNCTION();

		for (const auto& View : this->_App->_Modules)
		{
			for (const auto& Module : View)
			{
				Module->Procedure(E);
			}
		}

		this->_App->Procedure(E);
	}

	EventDispatcher::EventDispatcher(Application* App)
	{
		this->_App = App;
	}
}