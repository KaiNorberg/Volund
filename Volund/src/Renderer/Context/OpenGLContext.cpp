#include "PCH/PCH.h"
#include "OpenGLContext.h"
#include "Context.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>

#include <glad/include/glad/glad.h>
#include <wglext/wglext.h>

namespace Volund
{
	void OpenGLContext::MakeCurrent()
	{
		if (wglGetCurrentContext() != this->_RenderingContext)
		{
			VOLUND_ASSERT(wglMakeCurrent((HDC)this->_DeviceContext, (HGLRC)this->_RenderingContext), "Failed to make OpenGL Context current");
		}
	}

	void OpenGLContext::SetVSync(bool Enabled)
	{
		if (WGLExtensionSupported("WGL_EXT_swap_control"))
		{
			auto wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

			wglSwapIntervalEXT(Enabled);
		}
		else
		{
			VOLUND_ERROR("VSync not souported!");
		}
	}

	bool OpenGLContext::WGLExtensionSupported(std::string_view Name) const
	{
		auto _wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)wglGetProcAddress("wglGetExtensionsStringEXT");

		return strstr(_wglGetExtensionsStringEXT(), Name.data()) != nullptr;
	}

	OpenGLContext::OpenGLContext(void* DeviceContext)
	{
		this->_DeviceContext = DeviceContext;

		VOLUND_INFO("Creating OpenGL context...");

		this->_RenderingContext = wglCreateContext((HDC)DeviceContext);
		VOLUND_ASSERT(this->_RenderingContext, "Failed to create OpenGL context");

		this->MakeCurrent();
	}

	OpenGLContext::~OpenGLContext()
	{
		if (this->_RenderingContext)
		{
			if (wglGetCurrentContext() == this->_RenderingContext)
			{
				wglMakeCurrent(nullptr, nullptr);
			}

			wglDeleteContext((HGLRC)this->_RenderingContext);
		}
	}
}
