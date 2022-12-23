#pragma once

#include "../Module.h"

#include "Window/Window.h"
#include "Renderer/Context/Context.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"
#include "Renderer/Renderer.h"

namespace Volund
{
	class WindowModule : public Module
	{
	public:

		Ref<Window> GetWindow();

		void OnAttach(Application* App) override;

		void OnDetach() override;

		void Procedure(const Event& E) override;

		WindowModule();

	private:	

		Ref<Window> _Window;
	};
}