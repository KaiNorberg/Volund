#pragma once

#include "../Module.h"

#include "Window/Window.h"

namespace Volund
{
	class WindowModule : public Module
	{
	public:

		Ref<Window> GetWindow();

		void OnAttach(Application* app) override;

		void OnDetach() override;

		void Procedure(const Event& e) override;

		Ref<Window> operator->()
		{
			return this->GetWindow();
		}

		WindowModule();

	private:	

		Ref<Window> m_Window;
	};
}