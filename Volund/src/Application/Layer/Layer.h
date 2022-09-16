#pragma once

#include "Time/Time.h"

#include "EventDispatcher/Event.h"

namespace Volund
{
	class Application;

	class Layer
	{
	public:

		template <typename T>
		Ref<T> GetLayer(uint32_t Index = 0);

		Application* GetApp();

		virtual void OnAttach() {};

		virtual void OnDetach() {};

		virtual void OnUpdate(TimeStep) {};
	
		virtual void OnEvent(Event*) {};

		virtual ~Layer() {}

	private:		
		friend class Application;

		void SetParent(Application* Parent);

		Application* _Parent = nullptr;
	};

	template<typename T>
	inline Ref<T> Layer::GetLayer(uint32_t Index)
	{
		return this->GetApp()->GetLayer<T>(Index);
	}
}