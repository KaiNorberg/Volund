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
		Ref<T> GetModule();

		template<typename T>
		bool HasModule();

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
		if (this->HasModule<T>())
		{
			VOLUND_ERROR("Module of specifed type already attached!");
		}

		this->_Modules.PushBack(NewModule);
		NewModule->OnAttach(this);
	}

	template<typename T>
	void Application::AttachModule(Ref<T> NewModule)
	{
		if (this->HasModule<T>())
		{
			VOLUND_ERROR("Module of specifed type already attached!");
		}

		this->_Modules.PushBack(NewModule);
		NewModule->OnAttach(this);
	}

	template<typename T>
	inline Ref<T> Application::GetModule()
	{
		return this->_Modules.Get<T>();
	}

	template<typename T>
	inline bool Application::HasModule()
	{
		return this->_Modules.Contains<T>();
	}
}
