#include "PCH/PCH.h"

#include "EventDispatcher.h"
#include "Input/Input.h"

#include "Application/Application.h"

namespace Volund
{
	void EventDispatcher::ConnectApp(WeakRef<Application> App)
	{
		_Apps.push_back(App);
	}

	void EventDispatcher::SendEventToApps(Event* E)
	{
		for (int i = 0; i < _Apps.size(); i++)
		{
			if (!_Apps[i].expired())
			{
				auto LockedRef = _Apps[i].lock();

				LockedRef->EventCallback(E);
			}
			else
			{
				_Apps.erase(_Apps.begin() + i);
				i--;
			}
		}
	}
}