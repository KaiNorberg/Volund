#include "PCH/PCH.h"
#include "Mesh.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#include "OpenGLMesh.h"

#include "ModelLoader/ModelLoader.h"

namespace Volund
{
	std::string Mesh::GetFilepath()
	{
		return this->_Filepath;
	}

	Ref<Vertexbuffer> Mesh::GetVertexbuffer()
	{
		return this->_Vertexbuffer;
	}

	Ref<Indexbuffer> Mesh::GetIndexbuffer()
	{
		return this->_Indexbuffer;
	}

	const Ref<Vertexbuffer> Mesh::GetVertexbuffer() const
	{
		return this->_Vertexbuffer;
	}

	const Ref<Indexbuffer> Mesh::GetIndexbuffer() const
	{
		return this->_Indexbuffer;
	}

	Ref<Mesh> Mesh::Create(std::string_view Filepath)
	{
		ModelLoader<float, uint32_t> Loader = ModelLoader<float, uint32_t>(Filepath);

		Ref<Vertexbuffer> VBuffer = Vertexbuffer::Create(Loader.Vertices.data(), (uint32_t)Loader.Vertices.size());
		VBuffer->SetLayout({ VertexAttributeType::FLOAT3, VertexAttributeType::FLOAT2, VertexAttributeType::FLOAT3 });

		Ref<Indexbuffer> IBuffer = Indexbuffer::Create(Loader.Indices.data(), (uint32_t)Loader.Indices.size());

		Ref<Mesh> NewMesh = Mesh::Create(VBuffer, IBuffer);
		NewMesh->_Filepath = Filepath;

		return NewMesh;
	}

	Ref<Mesh> Mesh::Create(Ref<Vertexbuffer>& VBuffer, Ref<Indexbuffer>& IBuffer)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case RenderingAPI::API::OPENGL:
		{
			return std::make_shared<OpenGLMesh>(VBuffer, IBuffer);
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
