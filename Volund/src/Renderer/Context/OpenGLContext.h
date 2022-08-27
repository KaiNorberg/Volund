#pragma once

#include "Context.h"
#include "Window/Window.h"

namespace Volund
{
	class OpenGLContext : public Context
	{
	public:

		void Flush() override;

		OpenGLContext(Window* window);
		
		~OpenGLContext();

	private:
		
		Window* _Window;
	};
}

