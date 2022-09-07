#include "PCH/PCH.h"

#include "Editor.h"

using namespace Volund;

#define LOAD_SCENE

Editor::Editor()
{
	Ref<GameLayer> NewLayer = Ref<GameLayer>(new GameLayer());

#ifndef LOAD_SCENE

	Ref<Scene> NewScene = Ref<Scene>(new Scene());

	auto TestShader = NewScene->Assets.Create<ShaderAsset>("Standard/Shaders/Test.shader");
	auto TeapotMesh = NewScene->Assets.Create<MeshAsset>("Standard/Models/Teapot.obj");
	auto CubeMesh = NewScene->Assets.Create<MeshAsset>("Standard/Models/Cube.obj");

	auto TestMaterial = NewScene->Assets.Create<MaterialAsset>("Test.material");

	Ref<Entity> CameraEntity = NewScene->CreateEntity("CameraEntity", Vec3(0.0f, 2.0f, 10.0f));
	CameraEntity->CreateComponent<Camera>()->SetActive();
	CameraEntity->CreateComponent<CameraMovement>(5.0f, 1.0f);

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