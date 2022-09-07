#pragma once

#include "Context.h"
#include "Window/Window.h"

namespace Volund
{
	class OpenGLContext : public Context
	{
	public:

		void MakeCurrent() override;

		void SetVSync(bool Enabled) override;

		void Flush() override;

		OpenGLContext(Ref<Window> const& window);
		
		~OpenGLContext();

	private:

		bool WGLExtensionSupported(std::string const& Name);

		void* _RenderingContext = nullptr;

		Ref<Window> _Window;
	};
}

