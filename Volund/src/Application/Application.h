#pragma once

#include "Layer/Layer.h"

#include "Container/Container.h"

#include "EventDispatcher/EventDispatcher.h"

namespace Volund
{
	class Application
	{
	public:

		void Run();

		Ref<EventDispatcher> GetEventDispatcher();

		template <typename T>
		void AttachLayer(T* L);

		template <typename T>
		Ref<T> GetLayer(int Index = 0);

		void Terminate();

		bool ShouldRun() const;

		void OnEvent(Event* E);

		Application();

		virtual ~Application();

	protected:
		bool _ShouldRun = true;

	private:
		
		void Loop() const;

		Ref<EventDispatcher> _EventDispatcher;

		Container<Layer> _LayerContainer;
	};

	template<typename T>
	inline void Application::AttachLayer(T* L)
	{
		this->_LayerContainer.PushBack(Ref<T>(L));
		L->SetParent(this);
		L->OnAttach();
	}

	template<typename T>
	inline Ref<T> Application::GetLayer(int Index)
	{
		return this->_LayerContainer.Get<T>(Index);
	}
}
