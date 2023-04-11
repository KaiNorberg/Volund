#include "PCH/PCH.h"
#include "Mesh.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#include "OpenGLMesh.h"

#include "ModelLoader/ModelLoader.h"

#include "ThreadPool/ThreadPool.h"
#include "DelayedTaskHandler/DelayedTaskHandler.h"

namespace Volund
{
	AABB Mesh::GetAABB(const Mat4x4& modelMatrix)
	{
		return this->m_Aabb.ToWorldSpace(modelMatrix);
	}

	std::string Mesh::GetFilepath()
	{
		return this->m_Filepath;
	}

	Ref<VertexBuffer> Mesh::GetVertexBuffer()
	{
		return this->m_VertexBuffer;
	}

	Ref<IndexBuffer> Mesh::GetIndexBuffer()
	{
		return this->m_IndexBuffer;
	}

	const Ref<VertexBuffer> Mesh::GetVertexBuffer() const
	{
		return this->m_VertexBuffer;
	}

	const Ref<IndexBuffer> Mesh::GetIndexBuffer() const
	{
		return this->m_IndexBuffer;
	}

	Ref<Mesh> Mesh::Create(const std::string& filepath)
	{
		Ref<Mesh> newMesh = Mesh::Create();

		VOLUND_THREADPOOL_SUBMIT([filepath, newMesh]()
		{		
			newMesh->m_Filepath = filepath;

			ModelLoader<float, uint32_t> Loader = ModelLoader<float, uint32_t>(filepath);

			newMesh->m_Aabb = Loader.aabb;

			DelayedTaskHandler::DelayTask([newMesh, Loader]()
			{			
				Ref<VertexBuffer> VBuffer = VertexBuffer::Create(Loader.Vertices.data(), (uint32_t)Loader.Vertices.size());
				VBuffer->SetLayout({ VertexAttributeType::Float3, VertexAttributeType::Float2, VertexAttributeType::Float3 });

				Ref<IndexBuffer> IBuffer = IndexBuffer::Create(Loader.Indices.data(), (uint32_t)Loader.Indices.size());

				newMesh->SetVertexBuffer(VBuffer);
				newMesh->SetIndexBuffer(IBuffer);
			});
		});

		return newMesh;
	}

	Ref<Mesh> Mesh::Create()
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLMesh>();
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

	Ref<Mesh> Mesh::Create(Ref<VertexBuffer>& VertexBuffer, Ref<IndexBuffer>& IndexBuffer)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLMesh>(VertexBuffer, IndexBuffer);
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
