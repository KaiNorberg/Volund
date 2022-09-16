#include "PCH/PCH.h"

#include "EditorLayer.h"

#include "VML/VML.h"

Ref<Window> EditorLayer::GetWindow()
{
	return this->_Window;
}

void EditorLayer::LoadScene(const std::filesystem::path& FilePath)
{
	this->_CurrentScene = Scene::Deserialize(FilePath.string());
}

void EditorLayer::LoadProject(const std::filesystem::path& FilePath)
{
	std::filesystem::current_path(FilePath.parent_path());
	this->_CurrentProject = VML(FilePath.string());
}

void EditorLayer::OnAttach()
{
	this->_API = RenderingAPI::Create(RenderingAPI::API::OPENGL);

	auto NewEventDispatcher = Ref<EventDispatcher>(new EventDispatcher(this));
	this->_Window = Ref<Window>(new Window(NewEventDispatcher, 500, 500, false));

	this->_Window->SetTitle("Volund Editor");
	this->_Window->SetCursorMode("Normal");
	this->_Window->SetFocus();

	this->_Context = Context::Create(this->_Window);
	this->_Context->SetVSync(true);
	this->_Context->MakeCurrent();

	Renderer::Init(this->_API);
}

void EditorLayer::OnDetach()
{

}

void EditorLayer::OnUpdate(TimeStep TS)
{
	this->_Context->MakeCurrent();
	this->_Context->Flush();
	this->_API->Clear();

	Camera* ActiveCamera = Camera::GetActiveCamera(this->_CurrentScene);

	if (ActiveCamera != nullptr)
	{
		Mat4x4 ViewProjMatrix = ActiveCamera->GetProjectionMatrix(this->_Context->GetWindow()->GetAspectRatio()) * ActiveCamera->GetViewMatrix();
		Vec3 EyePosition = ActiveCamera->GetEntity()->GetComponent<Transform>()->Position;
		auto& PointLights = this->_CurrentScene->ComponentView<PointLight>();

		Renderer::BeginScene(ViewProjMatrix, EyePosition, PointLights);

		if (_CurrentScene != nullptr)
		{
			this->_CurrentScene->OnUpdate(TS);
		}
	
		Renderer::EndScene(this->_Context);
	}
	else
	{
		if (_CurrentScene != nullptr)
		{
			this->_CurrentScene->OnUpdate(TS);
		}
	}

	this->_Window->Update();
}

void EditorLayer::OnEvent(Event* E)
{
	switch (E->GetType())
	{
	case EventType::WINDOW_CLOSE:
	{
		this->GetApp()->Terminate();
	}
	break;
	}

	if (this->_CurrentScene != nullptr)
	{
		this->_CurrentScene->OnEvent(E);
	}
}
