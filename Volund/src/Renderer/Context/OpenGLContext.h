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

		OpenGLContext(Ref<Window> const& TargetWindow);
		
		~OpenGLContext();

	private:

		bool WGLExtensionSupported(std::string const& Name) const;

		void* _RenderingContext = nullptr;
	};
}

