#pragma once

#include "Window/Window.h"

namespace Volund
{
	struct LuaWindow
	{
	public:

		void SetCursorMode(CursorMode NewMode);

		void SetTitle(std::string Title);

		void SetVsync(bool Enabled);

		LuaWindow(Ref<Window> window);

	private:

		Ref<Window> _Window;

	};
}