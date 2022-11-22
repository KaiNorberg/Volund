#pragma once

#include "Module/Module.h"

#include "Time/Time.h"
#include "Container/Container.h"
#include "EventDispatcher/EventDispatcher.h"

namespace Volund
{
	class Application
	{
	public:

		void Run();

		void Terminate();

		bool ShouldRun() const;

		Ref<EventDispatcher> GetEventDispatcher();

		void AttachModule(Module* NewModule);

		void AttachModule(Ref<Module> NewModule);

		template<typename T>
		Ref<T> GetModule(int Index = 0);

		void EventCallback(Event* E);

		virtual void OnEvent(Event* E);
		
		virtual void OnUpdate(TimeStep TS);

		virtual void OnRun();

		virtual void OnTerminate();

		Application();

		virtual ~Application();

	private:
		
		void Loop();

		bool _ShouldRun = true;

	protected:

		Container<Module> _Modules;

		Ref<EventDispatcher> _EventDispatcher;
	};

	template<typename T>
	inline Ref<T> Application::GetModule(int Index)
	{
		return this->_Modules.Get<T>(Index);
	}
}
