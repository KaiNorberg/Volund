#include "PCH/PCH.h"
#include "Mesh.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#include "OpenGLMesh.h"

namespace Volund
{
	Ref<VertexBuffer> Mesh::GetVertexBuffer()
	{
		return this->_VertexBuffer;
	}

	Ref<IndexBuffer> Mesh::GetIndexBuffer()
	{
		return this->_IndexBuffer;
	}

	const Ref<VertexBuffer> Mesh::GetVertexBuffer() const
	{
		return this->_VertexBuffer;
	}

	const Ref<IndexBuffer> Mesh::GetIndexBuffer() const
	{
		return this->_IndexBuffer;
	}

	Ref<Mesh> Mesh::Create(Ref<VertexBuffer>& VBuffer, Ref<IndexBuffer>& IBuffer)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case RenderingAPI::API::OPENGL:
		{
			return Ref<Mesh>(new OpenGLMesh(VBuffer, IBuffer));
		}
		break;
		default:
		{
			VOLUND_ERROR("Creating a Mesh without a specified GraphicsAPI!");
			return nullptr;
		}
		break;
		}
	}
}