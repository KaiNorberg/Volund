#include "PCH/PCH.h"

#include "EventDispatcher.h"
#include "Input/Input.h"

#include "Application/Application.h"

namespace Volund
{
	void EventDispatcher::Dispatch(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();
	
		if (this->m_App == nullptr)
		{
			VOLUND_WARNING("Event dispatcher not connected!");
			return;
		}

		this->m_App->Procedure(e);

		for (const auto& [TypeID, View] : this->m_App->m_Modules)
		{
			for (const auto& module : View)
			{
				module->Procedure(e);
			}
		}
	}

	void EventDispatcher::Connect(Ref<Application> app)
	{
		this->m_App = app;
	}

	EventDispatcher::EventDispatcher()
	{

	}
}