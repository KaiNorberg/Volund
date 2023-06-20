#pragma once

#include "Module/Module.h"

#include "Time/Time.h"
#include "PolyContainer/PolyContainer.h"
#include "EventDispatcher/EventDispatcher.h"
#include "ThreadPool/ThreadPool.h"

namespace Volund
{
	class Application
	{
	public:

		void Run();

		bool ShouldRun() const;

		Ref<EventDispatcher> GetDispatcher();

		template<typename T>
		void AttachModule(T* newModule);

		template<typename T>
		void AttachModule(Ref<T> newModule);

		template<typename T>
		Ref<T> GetModule();

		template<typename T>
		bool HasModule();
		virtual void OnRun() {}
		virtual void OnTerminate() {}
		virtual void Procedure(const Event& e) {}

		Application();

		virtual ~Application();

	private:

		friend class EventDispatcher;

		void Loop();

		void Dispatch(const Event& e);

		bool m_ShouldRun = true;

		Ref<EventDispatcher> m_EventDispatcher;

	protected:

		void Terminate();

		PolyContainer<Module> m_Modules;
	};

	template<typename T>
	void Application::AttachModule(T* newModule)
	{
		if (this->HasModule<T>())
		{
			VOLUND_ERROR("Module of specifed type already attached!");
		}

		this->m_Modules.PushBack(newModule);
		newModule->OnAttach(this);
	}

	template<typename T>
	void Application::AttachModule(Ref<T> newModule)
	{
		if (this->HasModule<T>())
		{
			VOLUND_ERROR("Module of specifed type already attached!");
		}

		this->m_Modules.PushBack(newModule);
		newModule->OnAttach(this);
	}

	template<typename T>
	inline Ref<T> Application::GetModule()
	{
		if (!this->HasModule<T>())
		{
			VOLUND_ERROR("Application does not have Module of specifed type!");
		}

		return this->m_Modules.Get<T>();
	}

	template<typename T>
	inline bool Application::HasModule()
	{
		return this->m_Modules.Contains<T>();
	}

	Ref<Application> Entry();
}
