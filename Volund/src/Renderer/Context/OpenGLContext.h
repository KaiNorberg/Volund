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

		OpenGLContext(const Ref<Window>& TargetWindow);
		
		~OpenGLContext();

	private:

		bool WGLExtensionSupported(const std::string& Name) const;

		void* _RenderingContext = nullptr;
	};
}

