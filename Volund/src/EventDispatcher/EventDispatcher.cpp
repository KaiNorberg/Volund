#include "PCH/PCH.h"

#include "EventDispatcher.h"
#include "Input/Input.h"

#include "Application/Application.h"

namespace Volund
{
	void EventDispatcher::Dispatch(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		for (const auto& [TypeID, View] : this->m_App->m_Modules)
		{
			for (const auto& module : View)
			{
				module->Procedure(e);
			}
		}

		this->m_App->Procedure(e);
	}

	EventDispatcher::EventDispatcher(Application* app)
	{
		this->m_App = app;
	}
}