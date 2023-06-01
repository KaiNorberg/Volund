#pragma once

#include "../Module.h"

#include "Window/Window.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"
#include "Renderer/Renderer.h"

namespace Volund
{
	class WindowModule : public Module
	{
	public:

		Ref<Window> GetWindow();

		void OnAttach(Application* app) override;

		void OnDetach() override;

		void Procedure(const Event& e) override;

		WindowModule();

	private:	

		Ref<Window> m_Window;
	};
}