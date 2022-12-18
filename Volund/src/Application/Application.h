#pragma once

#include "Module/Module.h"

#include "Time/Time.h"
#include "Container/Container.h"
#include "Core/EventDispatcher/EventDispatcher.h"

namespace Volund
{
	class Application
	{
	public:

		void Run();

		void Terminate();

		bool ShouldRun() const;

		template<typename T>
		void AttachModule(T* NewModule);

		template<typename T>
		void AttachModule(Ref<T> NewModule);

		template<typename T>
		Ref<T> GetModule(int Index = 0);

		template<typename T>
		bool HasModule(int Index = 0);

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
	};

	template<typename T>
	void Application::AttachModule(T* NewModule)
	{
		this->_Modules.PushBack(NewModule);
		NewModule->OnAttach(this);
	}

	template<typename T>
	void Application::AttachModule(Ref<T> NewModule)
	{
		this->_Modules.PushBack(NewModule);
		NewModule->OnAttach(this);
	}

	template<typename T>
	inline Ref<T> Application::GetModule(int Index)
	{
		return this->_Modules.Get<T>(Index);
	}

	template<typename T>
	inline bool Application::HasModule(int Index)
	{
		return this->_Modules.Contains<T>(Index);
	}
}
