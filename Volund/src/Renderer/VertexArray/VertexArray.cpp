#include "PCH/PCH.h"
#include "VertexArray.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#include "OpenGLVertexArray.h"

namespace Volund
{
	Ref<VertexBuffer> VertexArray::GetVertexBuffer()
	{
		return this->_VertexBuffer;
	}

	Ref<IndexBuffer> VertexArray::GetIndexBuffer()
	{
		return this->_IndexBuffer;
	}

	const Ref<VertexBuffer> VertexArray::GetVertexBuffer() const
	{
		return this->_VertexBuffer;
	}

	const Ref<IndexBuffer> VertexArray::GetIndexBuffer() const
	{
		return this->_IndexBuffer;
	}

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

	VertexArray* VertexArray::Create(Ref<VertexBuffer>& VBuffer, Ref<IndexBuffer>& IBuffer)
	{
		switch (RenderingAPI::GetAPI())
		{
		case RenderingAPI::API::OPENGL:
		{
			return new OpenGLVertexArray(VBuffer, IBuffer);
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