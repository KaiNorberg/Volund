#pragma once

#include "Module/Module.h"

#include "Time/Time.h"
#include "Container/Container.h"
#include "EventDispatcher/EventDispatcher.h"
#include "ThreadPool/ThreadPool.h"

namespace Volund
{
	class Application
	{
	public:

		void Run();

		bool ShouldRun() const;

		Ref<EventDispatcher> GetEventDispatcher();

		template<typename T>
		void AttachModule(T* NewModule);

		template<typename T>
		void AttachModule(Ref<T> NewModule);

		template<typename T>
		Ref<T> GetModule(int Index = 0);

		template<typename T>
		bool HasModule(int Index = 0);

		virtual void OnRun() = 0;
		virtual void OnTerminate() = 0;
		virtual void Procedure(const Event& E) = 0;

		Application();

		virtual ~Application();

	private:

		friend class EventDispatcher;

		void Loop();

		bool _ShouldRun = true;

		Ref<EventDispatcher> _EventDispatcher;

	protected:

		void Terminate();

 		ThreadPool _ThreadPool;

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
