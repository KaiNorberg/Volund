#include "PCH/PCH.h"

#include "GameLayer.h"

#include "Renderer/Renderer.h"

namespace Volund
{
	void GameLayer::OnAttach()
	{
		float TriangleVertices[] =
		{
			-0.5f, -0.5, 0.0,    1.0, 0.0, 0.0, 1.0,
			 0.5,  -0.5, 0.0,    0.0, 1.0, 0.0, 1.0,
			 0.0,   0.5, 0.0,    0.0, 0.0, 1.0, 1.0
		};
		uint32_t TriangleIndices[] = { 0, 1, 2 };

		float SquareVertices[] =
		{
			-0.8,  -0.8, 0.0,    0.0, 0.0, 1.0, 1.0,
			 0.8,  -0.8, 0.0,    0.0, 0.0, 1.0, 1.0,
			-0.8,   0.8, 0.0,    1.0, 0.0, 0.0, 1.0,
			-0.8,   0.8, 0.0,    1.0, 0.0, 0.0, 1.0,
			 0.8,  -0.8, 0.0,    0.0, 0.0, 1.0, 1.0,
			 0.8,   0.8, 0.0,    1.0, 0.0, 0.0, 1.0
		};
		uint32_t SquareIndices[] = { 0, 1, 2, 3, 4, 5 };

		_TestShader.reset(Shader::Create("Shaders/Test.shader"));

		Ref<VertexBuffer> TriangleVertexBuffer = Ref<VertexBuffer>(VertexBuffer::Create(TriangleVertices, sizeof(TriangleVertices) / sizeof(float)));
		Ref<IndexBuffer> TriangleIndexBuffer = Ref<IndexBuffer>(IndexBuffer::Create(TriangleIndices, sizeof(TriangleIndices) / sizeof(uint32_t)));
		TriangleVertexBuffer->SetLayout({ VertexAttributeType::FLOAT3, VertexAttributeType::FLOAT4 });
		this->_TriangleVertexArray.reset(VertexArray::Create(TriangleVertexBuffer, TriangleIndexBuffer));		
		
		Ref<VertexBuffer> SquareVertexBuffer = Ref<VertexBuffer>(VertexBuffer::Create(SquareVertices, sizeof(SquareVertices) / sizeof(float)));
		Ref<IndexBuffer> SquareIndexBuffer = Ref<IndexBuffer>(IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t)));
		SquareVertexBuffer->SetLayout({ VertexAttributeType::FLOAT3, VertexAttributeType::FLOAT4 });
		this->_SquareVertexArray.reset(VertexArray::Create(SquareVertexBuffer, SquareIndexBuffer));
	}

	void GameLayer::OnDetach()
	{

	}

	void GameLayer::OnUpdate(TimeStep TS)
	{
		Renderer::BeginScene();

		_TestShader->Use();
		Renderer::Submit(_SquareVertexArray);
		Renderer::Submit(_TriangleVertexArray);

		if (_LoadedScene != nullptr)
		{
			this->_LoadedScene->OnUpdate(TS);
		}

		Renderer::EndScene();
	}
}