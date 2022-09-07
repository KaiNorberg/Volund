#pragma once

#include "Context.h"
#include "Window/Window.h"

namespace Volund
{
	class OpenGLContext : public Context
	{
	public:

		void Flush() override;

		OpenGLContext(Ref<Window> const& window);
		
		~OpenGLContext();

	private:
		
		Ref<Window> _Window;
	};
}

