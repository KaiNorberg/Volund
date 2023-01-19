#pragma once

#include "RenderingContext.h"
#include "Window/Window.h"

namespace Volund
{
	class OpenGLContext : public RenderingContext
	{
	public:

		void MakeCurrent() override;

		void SetVSync(bool Enabled) override;

		OpenGLContext(void* DeviceContext);
		
		~OpenGLContext();

	private:

		bool WGLExtensionSupported(std::string_view Name) const;

		void* _DeviceContext = nullptr;

		void* _RenderingContext = nullptr;
	};
}

