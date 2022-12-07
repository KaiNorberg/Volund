#pragma once

#include "../Module.h"

#include "Core/Window/Window.h"
#include "Renderer/Context/Context.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"
#include "Renderer/Renderer.h"

namespace Volund
{
	class WindowModule : public Module
	{
	public:

		void OnEvent(Event* E) override;

		void OnUpdate(TimeStep TS) override;

		void OnAttach(Application* App) override;

		void OnDestroy() override;

		WindowModule();

	private:	
	};
}