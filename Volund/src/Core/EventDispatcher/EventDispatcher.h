#pragma once

#include "Event.h"

#include "Core/Scene/Scene.h"

namespace Volund
{
	class Application;

	class EventDispatcher
	{
	public:

		template <typename T>
		static void Dispatch(T E);

		static void ConnectApp(WeakRef<Application> App);

	private:

		EventDispatcher() = delete;

		static void SendEventToApps(Event* E);

		static inline std::vector<WeakRef<Application>> _Apps;
	};

	template <typename T>
	void EventDispatcher::Dispatch(T E)
	{
		Scene::EventCallback(static_cast<Event*>(&E));
		SendEventToApps(static_cast<Event*>(&E));
	}
}
