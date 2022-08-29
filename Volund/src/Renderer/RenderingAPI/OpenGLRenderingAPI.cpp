#include "PCH/PCH.h"

#include "OpenGLRenderingAPI.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	void OpenGLRenderingAPI::SetClearColor(RGBA const& Color)
	{
		glClearColor(Color.r, Color.g, Color.b, Color.a);
	}

	void OpenGLRenderingAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderingAPI::DrawIndexed(Ref<VertexArray> const& VArray)
	{
		glDrawElements(GL_TRIANGLES, VArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}