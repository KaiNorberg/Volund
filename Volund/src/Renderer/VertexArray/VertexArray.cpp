#include "PCH/PCH.h"
#include "VertexArray.h"

#include "Renderer/Renderer.h"

#include "OpenGLVertexArray.h"

namespace Volund
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case GraphicsAPI::OPENGL:
		{
			return new OpenGLVertexArray();
		}
		break;
		default:
		{
			VOLUND_ERROR("Creating a VertexBuffer without a specified GraphicsAPI!");
			return nullptr;
		}
		break;
		}
	}
}