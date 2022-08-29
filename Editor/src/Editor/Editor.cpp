#include "PCH/PCH.h"

#include "Editor.h"

using namespace Volund;

class CameraMovement : public Component
{
public:
	void OnUpdate(TimeStep TS) override
	{
		if (Input::IsHeld('W'))
		{
			Transform* EntityTransform = this->GetEntity()->GetComponent<Transform>();

			EntityTransform->Position += EntityTransform->GetFront() * float(TS);
		}
		else if (Input::IsHeld('S'))
		{
			Transform* EntityTransform = this->GetEntity()->GetComponent<Transform>();

			EntityTransform->Position -= EntityTransform->GetFront() * float(TS);
		}
		else if (Input::IsHeld('A'))
		{
			Transform* EntityTransform = this->GetEntity()->GetComponent<Transform>();

			EntityTransform->Position -= EntityTransform->GetRight() * float(TS);
		}
		else if (Input::IsHeld('D'))
		{
			Transform* EntityTransform = this->GetEntity()->GetComponent<Transform>();

			EntityTransform->Position += EntityTransform->GetRight() * float(TS);
		}		
		
		static Vec3 Rotation = Vec3(0.0f);
		static Vec2 OldCursorPos = Input::GetCursorPosition();

		Vec2 Delta = Input::GetCursorPosition() - OldCursorPos;		
		
		Delta.x = Math::Clamp(Delta.x, -1.0f, 1.0f);
		Delta.y = Math::Clamp(Delta.y, -1.0f, 1.0f);

		Rotation -= Vec3(Delta.y, Delta.x, 0.0f);

		Rotation.x = Math::Clamp(Rotation.x, -89.0f, 89.0f);

		this->GetEntity()->GetComponent<Transform>()->SetRotation(Rotation);

		OldCursorPos = Input::GetCursorPosition();
	}
};

class TestScene : public Scene
{
public:

	Ref<VertexArray> _TriangleVertexArray;
	Ref<VertexArray> _SquareVertexArray;

	Ref<Shader> _TestShader;

	void OnUpdate(TimeStep TS)
	{
		Renderer::Submit(_SquareVertexArray, _TestShader);
		Renderer::Submit(_TriangleVertexArray, _TestShader);
	}

	TestScene()
	{
		float TriangleVertices[] =
		{
			-0.5f, -0.5, 0.5,    1.0, 0.0, 0.0, 1.0,
			 0.5,  -0.5, 0.5,    0.0, 1.0, 0.0, 1.0,
			 0.0,   0.5, 0.5,    0.0, 0.0, 1.0, 1.0
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

		Entity* CameraEntity = this->CreateEntity("CameraEntity");

		CameraEntity->CreateComponent<Transform>(Vec3(0.0f, 0.0f, 3.0f));
		CameraEntity->CreateComponent<Camera>()->SetActive();		
		CameraEntity->CreateComponent<CameraMovement>();
	}
};

Editor::Editor()
{
	GameLayer* NewLayer = new GameLayer();
	this->AttachLayer(NewLayer);
	NewLayer->LoadScene<TestScene>();
}

Application* Volund::CreateApplication()
{
	return new Editor();
}