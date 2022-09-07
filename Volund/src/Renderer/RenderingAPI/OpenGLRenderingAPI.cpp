#include "PCH/PCH.h"

#include "OpenGLRenderingAPI.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	void OpenGLRenderingAPI::SetViewPort(int32_t X, int32_t Y, int32_t Width, int32_t Height)
	{
		glViewport(X, Y, Width, Height);
	}

	void OpenGLRenderingAPI::SetClearColor(RGBA const& Color)
	{
		glClearColor(Color.r, Color.g, Color.b, Color.a);
	}

	void OpenGLRenderingAPI::Clear()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderingAPI::DrawIndexed(Ref<Mesh> const& VArray)
	{
		glDrawElements(GL_TRIANGLES, VArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}