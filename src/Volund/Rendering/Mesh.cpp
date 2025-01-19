#include "Rendering/Mesh.h"

#include "Rendering/RenderingAPI.h"

#include "Rendering/OpenGL/OpenGLMesh.h"

namespace Volund
{

	std::shared_ptr<Mesh> Mesh::Create(std::string const& filepath)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLMesh>(filepath);
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
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLMesh>(vertexBuffer, indexBuffer);
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