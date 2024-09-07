#include "PCH/PCH.h"
#include "Mesh.h"

#include "Rendering/RenderingAPI/RenderingAPI.h"

#include "OpenGLMesh.h"

#include "ModelLoader/ModelLoader.h"

namespace Volund
{
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

	Ref<Mesh> Mesh::Create(Ref<VertexBuffer> vertexBuffer, Ref<IndexBuffer> indexBuffer)
	{
		Ref<Mesh> newMesh = Mesh::Create();
		newMesh->SetVertexBuffer(vertexBuffer);
		newMesh->SetIndexBuffer(indexBuffer);

		return newMesh;
	}
}
