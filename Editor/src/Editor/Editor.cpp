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

			EntityTransform->Position += EntityTransform->GetFront() * float(TS) * 5.0f;
		}
		if (Input::IsHeld('S'))
		{
			Ref<Transform> EntityTransform = this->GetEntity()->GetComponent<Transform>();

			EntityTransform->Position -= EntityTransform->GetFront() * float(TS) * 5.0f;
		}
		if (Input::IsHeld('A'))
		{
			Ref<Transform> EntityTransform = this->GetEntity()->GetComponent<Transform>();

			EntityTransform->Position -= EntityTransform->GetRight() * float(TS) * 5.0f;
		}
		if (Input::IsHeld('D'))
		{
			Ref<Transform> EntityTransform = this->GetEntity()->GetComponent<Transform>();

			EntityTransform->Position += EntityTransform->GetRight() * float(TS) * 5.0f;
		}		
		
		static Vec3 Rotation = Vec3(0.0f);
		static DVec2 OldCursorPos = Input::GetCursorPosition();

		DVec2 Delta = Input::GetCursorPosition() - OldCursorPos;		
		
		Delta.x = Math::Clamp(Delta.x, -10.0, 10.0);
		Delta.y = Math::Clamp(Delta.y, -10.0, 10.0);

		Rotation -= Vec3(Delta.y, Delta.x, 0.0f);

		Rotation.x = Math::Clamp(Rotation.x, -89.0f, 89.0f);

		this->GetEntity()->GetComponent<Transform>()->SetRotation(Rotation);

		OldCursorPos = Input::GetCursorPosition();
	}
};

class TestScene : public Scene
{
public:

	void OnUpdate(TimeStep TS)
	{

	}

	TestScene()
	{
		Ref<Shader> _TestShader = Shader::Create("Shaders/Test.shader");
		Ref<Material> _TestMaterial = Material::Create(_TestShader);

		Ref<Mesh> TeapotMesh = Mesh::Create("Teapot.obj");
		Ref<Mesh> CubeMesh = Mesh::Create("Cube.obj");

		Ref<Entity> CameraEntity = this->CreateEntity("CameraEntity", Vec3(0.0f, 0.0f, 5.0f));
		CameraEntity->CreateComponent<Camera>()->SetActive();
		CameraEntity->CreateComponent<CameraMovement>();

		Ref<Entity> TeapotEnity = this->CreateEntity("TeapotEntity", Vec3(3.0f, 0.0f, 0.0f));
		TeapotEnity->CreateComponent<MeshRenderer>(CubeMesh, _TestMaterial);

		Ref<Entity> CubeEnity = this->CreateEntity("CubeEntity", Vec3(-3.0f, 0.0f, 0.0f));
		CubeEnity->CreateComponent<MeshRenderer>(TeapotMesh, _TestMaterial);

		Ref<Entity> RedPointLight = this->CreateEntity("RedPointLight", Vec3(10.0f, 5.0f, 0.0f));
		RedPointLight->CreateComponent<PointLight>(RGB(1.0f, 0.0f, 0.0f));

		Ref<Entity> BluePointLight = this->CreateEntity("BluePointLight", Vec3(-10.0f, 5.0f, 0.0f));
		BluePointLight->CreateComponent<PointLight>(RGB(0.0f, 0.0f, 1.0f));
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