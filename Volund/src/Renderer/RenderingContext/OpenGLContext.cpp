#include "PCH/PCH.h"
#include "OpenGLContext.h"
#include "RenderingContext.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>

#include <glad/include/glad/glad.h>
#include <wglext/wglext.h>

namespace Volund
{
	void OpenGLContext::MakeCurrent()
	{
		if (wglGetCurrentContext() != this->m_RenderingContext)
		{
			VOLUND_ASSERT(wglMakeCurrent((HDC)this->m_DeviceContext, (HGLRC)this->m_RenderingContext), "Failed to make OpenGL Context current");
		}
	}

	void OpenGLContext::SetVSync(bool enabled)
	{
		if (WGLExtensionSupported("WGL_EXT_swap_control"))
		{
			auto wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

			wglSwapIntervalEXT(enabled);
		}
		else
		{
			VOLUND_ERROR("VSync not souported!");
		}
	}

	bool OpenGLContext::WGLExtensionSupported(std::string_view name) const
	{
		auto _wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)wglGetProcAddress("wglGetExtensionsStringEXT");

		return strstr(_wglGetExtensionsStringEXT(), name.data()) != nullptr;
	}

	OpenGLContext::OpenGLContext(void* deviceContext)
	{
		this->m_DeviceContext = deviceContext;

		VOLUND_INFO("Creating OpenGL context...");

		this->m_RenderingContext = wglCreateContext((HDC)deviceContext);
		VOLUND_ASSERT(this->m_RenderingContext, "Failed to create OpenGL context");

		this->MakeCurrent();
	}

	OpenGLContext::~OpenGLContext()
	{
		if (this->m_RenderingContext)
		{
			if (wglGetCurrentContext() == this->m_RenderingContext)
			{
				wglMakeCurrent(nullptr, nullptr);
			}

			wglDeleteContext((HGLRC)this->m_RenderingContext);
		}
	}
}
