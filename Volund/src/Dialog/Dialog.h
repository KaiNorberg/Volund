#pragma once

#include "Window/Window.h"

namespace Volund
{
	class Dialog
	{
	public:

		static std::string OpenFolder(Ref<Window> window);

		static std::string OpenFile(Ref<Window> window);

		static void Message(const std::string& title, const std::string& message, const std::string& dialogType, const std::string& iconType);

	private:
	};
}