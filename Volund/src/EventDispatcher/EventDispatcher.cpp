#include "PCH/PCH.h"

#include "EventDispatcher.h"
#include "Input/Input.h"

#include "Application/Application.h"

namespace Volund
{
	void EventDispatcher::Dispatch(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();
	
		if (this->m_App.expired())
		{
			VOLUND_WARNING("Event dispatcher not connected!");
			return;
		}

		Ref<Application> appRef = this->m_App.lock();

		appRef->Procedure(e);

		for (const auto& [TypeID, View] : appRef->m_Modules)
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