#pragma once

#include "Event.h"

namespace Volund
{
	class Layer;

	class EventDispatcher
	{
	public:
		template <typename T>
		void Dispatch(T E);

		EventDispatcher(Layer* L);

		~EventDispatcher();

	private:
		void SendEventToLayer(Event* E) const;

		Layer* _Layer;
	};

	template <typename T>
	void EventDispatcher::Dispatch(T E)
	{
		this->SendEventToLayer(static_cast<Event*>(&E));
	}
}
