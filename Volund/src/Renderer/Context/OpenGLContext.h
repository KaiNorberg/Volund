#pragma once

#include "Context.h"
#include "Core/Window/Window.h"

namespace Volund
{
	class OpenGLContext : public Context
	{
	public:

		void MakeCurrent() override;

		void SetVSync(bool Enabled) override;

		void Flush() override;

		OpenGLContext(void* DeviceContext);
		
		~OpenGLContext();

	private:

		bool WGLExtensionSupported(std::string_view Name) const;

		void* _DeviceContext = nullptr;

		void* _RenderingContext = nullptr;
	};
}

