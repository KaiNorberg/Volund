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

	std::shared_ptr<Mesh> Mesh::Create(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer)
	{
		std::shared_ptr<Mesh> newMesh = Mesh::Create();
		newMesh->SetVertexBuffer(vertexBuffer);
		newMesh->SetIndexBuffer(indexBuffer);

		return newMesh;
	}
}
