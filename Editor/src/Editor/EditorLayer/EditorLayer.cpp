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
	if (this->_Project != nullptr)
	{
		return this->_Project->GetScene();
	}
	else
	{
		return nullptr;
	}
}

const Ref<Project> EditorLayer::GetProject()
{
	return this->_Project;
}

const Ref<RenderingAPI> EditorLayer::GetAPI()
{
	return this->_API;
}

void EditorLayer::LoadProject(const std::filesystem::path& Filepath)
{
	if (Filepath.empty())
	{
		return;
	}

	if (Filepath.extension() == ".vproj")
	{
		this->_Project = Ref<Project>(new Project(Filepath.string()));
	}
	else
	{
		VOLUND_WARNING("That is not a valid Project file!");
	}
}

void EditorLayer::OnAttach()
{
	this->_API = RenderingAPI::Create(RenderingAPI::OPENGL);

	this->_Window = Ref<Window>(new Window(this->GetApp()->GetEventDispatcher(), 1980, 1080, false));

	this->_Window->SetTitle("Volund Editor");
	this->_Window->SetCursorMode("Normal");
	this->_Window->SetFocus();

	this->_Context = Context::Create(this->_Window);
	this->_Context->SetVSync(true);
	this->_Context->MakeCurrent();

	Renderer::Init(new ForwardRenderer(this->_API));
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
}
