#include "PCH/PCH.h"
#include "LuaWindow.h"

namespace Volund
{
	void LuaWindow::SetCursorMode(CursorMode NewMode)
	{
		this->_Window->SetCursorMode(NewMode);
	}

	void LuaWindow::SetTitle(std::string Title)
	{
		this->_Window->SetTitle(Title);
	}

	void LuaWindow::SetVsync(bool Enabled)
	{
		this->_Window->SetVsync(Enabled);
	}

	LuaWindow::LuaWindow(Ref<Window> window)
	{
		this->_Window = window; 
	}
}