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

#define LOAD_SCENE

Editor::Editor()
{
	GameLayer* NewLayer = new GameLayer();

#ifndef LOAD_SCENE

	Ref<Scene> NewScene = Ref<Scene>(new Scene());

	auto TestShader = NewScene->Assets.Create<ShaderAsset>("Standard/Shaders/Test.shader");
	auto TeapotMesh = NewScene->Assets.Create<MeshAsset>("Standard/Models/Teapot.obj");
	auto CubeMesh = NewScene->Assets.Create<MeshAsset>("Standard/Models/Cube.obj");

	auto TestMaterial = NewScene->Assets.Create<MaterialAsset>("Test.material");

	Ref<Entity> CameraEntity = NewScene->CreateEntity("CameraEntity", Vec3(0.0f, 2.0f, 10.0f));
	CameraEntity->CreateComponent<Camera>()->SetActive();

	Ref<Entity> TeapotEnity = NewScene->CreateEntity("TeapotEntity", Vec3(3.0f, 0.0f, 0.0f));
	TeapotEnity->CreateComponent<MeshRenderer>(CubeMesh, TestMaterial);

	Ref<Entity> CubeEnity = NewScene->CreateEntity("CubeEntity", Vec3(-3.0f, 0.0f, 0.0f));
	CubeEnity->CreateComponent<MeshRenderer>(TeapotMesh, TestMaterial);

	Ref<Entity> RedPointLight = NewScene->CreateEntity("RedPointLight", Vec3(10.0f, 5.0f, 0.0f));
	RedPointLight->CreateComponent<PointLight>(RGB(1.0f, 0.0f, 0.0f));

	Ref<Entity> BluePointLight = NewScene->CreateEntity("BluePointLight", Vec3(-10.0f, 5.0f, 0.0f));
	BluePointLight->CreateComponent<PointLight>(RGB(0.0f, 0.0f, 1.0f));

	NewScene->Serialize("Test.scene");

#else

	Ref<Scene> NewScene = Scene::Deserialize("Test.scene");

#endif

	NewLayer->LoadScene(NewScene);

	this->AttachLayer(NewLayer);
}

Application* Volund::CreateApplication()
{
	return new Editor();
}