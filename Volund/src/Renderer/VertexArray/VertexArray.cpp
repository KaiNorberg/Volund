#include "PCH/PCH.h"
#include "VertexArray.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#include "OpenGLVertexArray.h"

namespace Volund
{
	VertexArray* VertexArray::Create()
	{
		switch (RenderingAPI::GetAPI())
		{
		case RenderingAPI::API::OPENGL:
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