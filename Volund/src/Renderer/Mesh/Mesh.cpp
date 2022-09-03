#include "PCH/PCH.h"
#include "Mesh.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"
#include "ModelLoader/ModelLoader.h"

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

	Ref<Mesh> Mesh::Create(std::string const& FilePath)
	{
		ModelLoader<float, uint32_t> Loader = ModelLoader<float, uint32_t>(FilePath);

		Ref<VertexBuffer> VBuffer = VertexBuffer::Create(Loader.Vertices.data(), (uint32_t)Loader.Vertices.size());
		VBuffer->SetLayout({ VertexAttributeType::FLOAT3, VertexAttributeType::FLOAT2, VertexAttributeType::FLOAT3 });

		Ref<IndexBuffer> IBuffer = IndexBuffer::Create(Loader.Indices.data(), (uint32_t)Loader.Indices.size());

		switch (RenderingAPI::GetAPI())
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

	Ref<Mesh> Mesh::Create(Ref<VertexBuffer>& VBuffer, Ref<IndexBuffer>& IBuffer)
	{
		switch (RenderingAPI::GetAPI())
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