#include "Mesh.h"

#include "Rendering/RenderingAPI/RenderingAPI.h"

#include "OpenGLMesh.h"

#include "ModelLoader/ModelLoader.h"

namespace Volund
{
	std::shared_ptr<Mesh> Mesh::Create()
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

	std::shared_ptr<Mesh> Mesh::Create(std::string const& filepath)
	{
        std::shared_ptr<Mesh> newMesh = Mesh::Create();
        std::shared_ptr<ModelLoader> modelLoader = std::make_shared<ModelLoader>();

        VOLUND_INFO("Loading Asset (%s)... ", filepath.c_str());

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
				return nullptr;
			}
		}

		std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(modelLoader->Vertices.data(), modelLoader->Vertices.size());
		vertexBuffer->SetLayout({ VertexAttributeType::Float3, VertexAttributeType::Float2, VertexAttributeType::Float3 });

		std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(modelLoader->Indices.data(), modelLoader->Indices.size());

		newMesh->SetVertexBuffer(vertexBuffer);
		newMesh->SetIndexBuffer(indexBuffer);

		return newMesh;
	}

	std::shared_ptr<Mesh> Mesh::Create(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer)
	{
		std::shared_ptr<Mesh> newMesh = Mesh::Create();
		newMesh->SetVertexBuffer(vertexBuffer);
		newMesh->SetIndexBuffer(indexBuffer);

		return newMesh;
	}
}
