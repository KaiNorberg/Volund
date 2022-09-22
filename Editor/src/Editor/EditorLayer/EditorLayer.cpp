#include "PCH/PCH.h"

#include "EditorLayer.h"

#include "VML/VML.h"

const Ref<Context> EditorLayer::GetContext()
{
	return this->_Context;
}

const Ref<Window> EditorLayer::GetWindow()
{
	return this->_Window;
}

const Ref<Scene> EditorLayer::GetScene()
{
	return this->_Scene;
}

const Ref<VML> EditorLayer::GetProject()
{
	return this->_Project;
}

const Ref<RenderingAPI> EditorLayer::GetAPI()
{
	return this->_API;
}

void EditorLayer::SaveScene(const std::filesystem::path& FilePath)
{
	if (this->_Scene != nullptr)
	{
		this->_Scene->Serialize(FilePath.string());
	}
	else
	{
		VOLUND_WARNING("Cant save a scene without a loaded scene!");
	}
}

void EditorLayer::LoadScene(const std::filesystem::path& FilePath)
{
	if (FilePath.empty())
	{
		return;
	}

	this->_Scene = Scene::Deserialize(FilePath.string());
}

void EditorLayer::LoadProject(const std::filesystem::path& FilePath)
{
	if (FilePath.empty())
	{
		return;
	}

	if (FilePath.extension() == ".vproj")
	{
		this->_Project = Ref<VML>(new VML(FilePath.string()));
		std::filesystem::current_path(FilePath.parent_path());
		this->LoadScene(this->_Project->Get("Scenes")[0].GetAs<std::string>());
	}
	else
	{
		VOLUND_WARNING("That is not a valid Project file!");
	}
}

void EditorLayer::OnAttach()
{
	this->_API = RenderingAPI::Create(RenderingAPI::API::OPENGL);

	this->_Window = Ref<Window>(new Window(this->GetApp()->GetEventDispatcher(), 1980, 1080, false));

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

	if (this->_Scene != nullptr)
	{
		this->_Scene->OnEvent(E);
	}
}
