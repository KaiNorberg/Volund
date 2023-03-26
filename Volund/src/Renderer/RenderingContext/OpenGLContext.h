#pragma once

#include "RenderingContext.h"
#include "Window/Window.h"

namespace Volund
{
	class OpenGLContext : public RenderingContext
	{
	public:

		void MakeCurrent() override;

		void SetVSync(bool enabled) override;

		OpenGLContext(void* deviceContext);
		
		~OpenGLContext();

	private:

		bool WGLExtensionSupported(std::string_view name) const;

		void* m_DeviceContext = nullptr;

		void* m_RenderingContext = nullptr;
	};
}

