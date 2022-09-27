#include "PCH/PCH.h"

#include "Editor.h"

#include "UI/UI.h"

const Ref<Context> Editor::GetContext()
{
	return this->_Context;
}

const Ref<Window> Editor::GetWindow()
{
	return this->_Window;
}

void Editor::OnRun()
{
	RenderingAPI::Select(GraphicsAPI::OPENGL);

	this->_Window = Ref<Window>(new Window(this->GetEventDispatcher(), 1980, 1080, false));

	this->_Window->SetTitle("Volund Editor");
	this->_Window->SetCursorMode("Normal");
	this->_Window->SetFocus();

	this->_Context = Context::Create(this->_Window);
	this->_Context->SetVSync(true);
	this->_Context->MakeCurrent();

	RenderingAPI::Init();
	Renderer::Init(new ForwardRenderer());

	this->_Project = Ref<Project>(new Project());

	this->_UI = Ref<UI>(new UI(this->_Window, this->_Project));

	this->_Window->Show();
}

void Editor::OnTerminate()
{

}

void Editor::OnUpdate(TimeStep TS)
{
	this->_Context->MakeCurrent();

	this->_UI->Draw(TS);

	this->_Context->Flush();
	RenderingAPI::Clear();
	this->_Window->Update();
}

void Editor::OnEvent(Event* E)
{
	this->_UI->OnEvent(E);

	switch (E->GetType())
	{
	case EventType::WINDOW_CLOSE:
	{
		this->Terminate();
	}
	break;
	}
}
