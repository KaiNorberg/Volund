#include "PCH/PCH.h"
#include "Mesh.h"

#include "Rendering/RenderingAPI/RenderingAPI.h"

#include "OpenGLMesh.h"

#include "ModelLoader/ModelLoader.h"

#include "ThreadPool/ThreadPool.h"
#include "DeferredTaskHandler/DeferredTaskHandler.h"

namespace Volund
{
	AABB Mesh::GetAABB(const Mat4x4& modelMatrix)
	{
		if (this->m_VertexBuffer == nullptr)
		{
			return AABB();
		}

		return this->m_VertexBuffer->GetAABB().ToWorldSpace(modelMatrix);
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

	Ref<Mesh> Mesh::Create(const std::string& filepath)
	{
		ModelLoader modelLoader;

		if (ResourceLibrary::IsResource(filepath))
		{
			modelLoader.ParseOBJ(ResourceLibrary::Fetch(filepath));
		}
		else
		{
			modelLoader.LoadFile(filepath);

			if (!modelLoader.Valid())
			{
				VOLUND_WARNING("Failed to load mesh %s!", filepath.c_str());
				return Mesh::Create();
			}
		}

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(modelLoader.Vertices.data(), modelLoader.Vertices.size());
		vertexBuffer->SetLayout({ VertexAttributeType::Float3, VertexAttributeType::Float2, VertexAttributeType::Float3 });

		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(modelLoader.Indices.data(), modelLoader.Indices.size());

		Ref<Mesh> newMesh = Mesh::Create();
		newMesh->SetVertexBuffer(vertexBuffer);
		newMesh->SetIndexBuffer(indexBuffer);

		return newMesh;
	}

	Ref<Mesh> Mesh::Create(Ref<VertexBuffer>& vertexBuffer, Ref<IndexBuffer>& indexBuffer)
	{
		Ref<Mesh> newMesh = Mesh::Create();
		newMesh->SetVertexBuffer(vertexBuffer);
		newMesh->SetIndexBuffer(indexBuffer);

		return newMesh;
	}

	Ref<Mesh> Mesh::CreateAsync(const std::string& filepath)
	{
		Ref<Mesh> newMesh = Mesh::Create();

		VOLUND_THREADPOOL_SUBMIT([newMesh, filepath]()
		{
			Ref<ModelLoader> modelLoader = std::make_shared<ModelLoader>();

			if (ResourceLibrary::IsResource(filepath))
			{
				modelLoader->ParseOBJ(ResourceLibrary::Fetch(filepath));
			}
			else
			{
				modelLoader->LoadFile(filepath);

				if (!modelLoader->Valid())
				{
					VOLUND_WARNING("Failed to load mesh %s!", filepath.c_str());
				}
			}

			DeferredTaskHandler::DeferTask([newMesh, modelLoader]()
			{
				Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(modelLoader->Vertices.data(), modelLoader->Vertices.size());
				vertexBuffer->SetLayout({ VertexAttributeType::Float3, VertexAttributeType::Float2, VertexAttributeType::Float3 });

				Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(modelLoader->Indices.data(), modelLoader->Indices.size());

				newMesh->SetVertexBuffer(vertexBuffer);
				newMesh->SetIndexBuffer(indexBuffer);
			});
		});

		return newMesh;
	}
}
