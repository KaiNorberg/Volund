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

		void OnEvent(Event* E) override;

		void OnUpdate(TimeStep TS) override;

		void OnRender() override;

		void OnAttach(Application* App) override;

		void OnDestroy() override;

		WindowModule();

	private:	

		Ref<Window> _Window;
	};
}