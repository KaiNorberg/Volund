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
			Ref<Transform> EntityTransform = this->GetEntity()->GetComponent<Transform>();

			EntityTransform->Position += EntityTransform->GetFront() * float(TS);
		}
		if (Input::IsHeld('S'))
		{
			Ref<Transform> EntityTransform = this->GetEntity()->GetComponent<Transform>();

			EntityTransform->Position -= EntityTransform->GetFront() * float(TS);
		}
		if (Input::IsHeld('A'))
		{
			Ref<Transform> EntityTransform = this->GetEntity()->GetComponent<Transform>();

			EntityTransform->Position -= EntityTransform->GetRight() * float(TS);
		}
		if (Input::IsHeld('D'))
		{
			Ref<Transform> EntityTransform = this->GetEntity()->GetComponent<Transform>();

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

	Ref<Mesh> _TriangleMesh;
	Ref<Mesh> _SquareMesh;

	Ref<Shader> _TestShader;
	Ref<Material> _TestMaterial;

	void OnUpdate(TimeStep TS)
	{

	}

	TestScene()
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
			-0.5,  -0.5, 0.0,    0.0, 0.0, 1.0, 1.0,
			 0.5,  -0.5, 0.0,    0.0, 0.0, 1.0, 1.0,
			-0.5,   0.5, 0.0,    1.0, 0.0, 0.0, 1.0,
			-0.5,   0.5, 0.0,    1.0, 0.0, 0.0, 1.0,
			 0.5,  -0.5, 0.0,    0.0, 0.0, 1.0, 1.0,
			 0.5,   0.5, 0.0,    1.0, 0.0, 0.0, 1.0
		};
		uint32_t SquareIndices[] = { 0, 1, 2, 3, 4, 5 };

		_TestShader = Shader::Create("Shaders/Test.shader");
		_TestMaterial = Material::Create(_TestShader);

		Ref<VertexBuffer> TriangleVertexBuffer = Ref<VertexBuffer>(VertexBuffer::Create(TriangleVertices, sizeof(TriangleVertices) / sizeof(float)));
		Ref<IndexBuffer> TriangleIndexBuffer = Ref<IndexBuffer>(IndexBuffer::Create(TriangleIndices, sizeof(TriangleIndices) / sizeof(uint32_t)));
		TriangleVertexBuffer->SetLayout({ VertexAttributeType::FLOAT3, VertexAttributeType::FLOAT4 });
		this->_TriangleMesh = Mesh::Create(TriangleVertexBuffer, TriangleIndexBuffer);

		Ref<VertexBuffer> SquareVertexBuffer = Ref<VertexBuffer>(VertexBuffer::Create(SquareVertices, sizeof(SquareVertices) / sizeof(float)));
		Ref<IndexBuffer> SquareIndexBuffer = Ref<IndexBuffer>(IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t)));
		SquareVertexBuffer->SetLayout({ VertexAttributeType::FLOAT3, VertexAttributeType::FLOAT4 });
		this->_SquareMesh = Mesh::Create(SquareVertexBuffer, SquareIndexBuffer);


		Ref<Entity> CameraEntity = this->CreateEntity("CameraEntity");
		Ref<Entity> TriangleEnity = this->CreateEntity("TriangleEnity");
		Ref<Entity> SquareEnity = this->CreateEntity("SquareEnity");

		CameraEntity->CreateComponent<Transform>(Vec3(0.0f, 0.0f, 0.0f));
		CameraEntity->CreateComponent<Camera>()->SetActive();		
		CameraEntity->CreateComponent<CameraMovement>();

		TriangleEnity->CreateComponent<Transform>(Vec3(0.0f, 0.0f, -2.0f));
		TriangleEnity->CreateComponent<MeshRenderer>(_TriangleMesh, _TestMaterial);

		SquareEnity->CreateComponent<Transform>(Vec3(0.0f, 0.0f, 2.0f));
		SquareEnity->CreateComponent<MeshRenderer>(_SquareMesh, _TestMaterial);
	}
};

Editor::Editor()
{
	GameLayer* NewLayer = new GameLayer();
	NewLayer->LoadScene<TestScene>();
	this->AttachLayer(NewLayer);
}

Application* Volund::CreateApplication()
{
	return new Editor();
}