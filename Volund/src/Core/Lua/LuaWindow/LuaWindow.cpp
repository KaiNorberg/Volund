#include "PCH/PCH.h"
#include "LuaWindow.h"

namespace Volund
{
	void LuaWindow::SetCursorMode(CursorMode NewMode)
	{
		Window::SetCursorMode(NewMode);
	}

	void LuaWindow::SetTitle(std::string Title)
	{
		Window::SetTitle(Title);
	}

	void LuaWindow::SetVsync(bool Enabled)
	{
		Window::SetVsync(Enabled);
	}
}