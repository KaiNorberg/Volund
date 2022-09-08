#include "PCH/PCH.h"
#include "OpenGLContext.h"
#include "Context.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include <windowsx.h>

#include <glad/glad.h>

#include <wglext/wglext.h>

namespace Volund
{
	void OpenGLContext::MakeCurrent()
	{
		if (wglGetCurrentContext() != this->_RenderingContext)
		{
			VOLUND_ASSERT(wglMakeCurrent((HDC)this->GetWindow()->GetDeviceContext(), (HGLRC)this->_RenderingContext),
			              "Failed to active OpenGL Context");
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

	void OpenGLContext::Flush()
	{
		GetWindow()->SwapBuffers();
	}

	bool OpenGLContext::WGLExtensionSupported(const std::string& Name) const
	{
		auto _wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)wglGetProcAddress(
			"wglGetExtensionsStringEXT");

		return strstr(_wglGetExtensionsStringEXT(), Name.c_str()) != nullptr;
	}

	OpenGLContext::OpenGLContext(const Ref<Window>& TargetWindow)
	{
		this->_Window = TargetWindow;

		VOLUND_INFO("Creating OpenGL context...");

		this->_RenderingContext = wglCreateContext((HDC)this->GetWindow()->GetDeviceContext());
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
