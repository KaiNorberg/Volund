#include "PCH/PCH.h"
#include "WindowModule.h"

#include "Application/Application.h"

namespace Volund
{
	void WindowModule::OnEvent(Event* E)
	{

	}

	void WindowModule::OnUpdate(TimeStep TS)
	{
		this->Window->Update();
	}

	void WindowModule::OnAttach(Application* App)
	{
		VL::RenderingAPI::Select(this->_SelectedAPI);

		this->Window = VL::Ref<VL::Window>(new VL::Window(App->GetEventDispatcher(), 1980, 1080, false));

		this->Window->SetTitle("Volund Editor");
		this->Window->SetCursorMode(VL::CursorMode::NORMAL);
		this->Window->SetFocus();

		this->Context = VL::Context::Create(this->Window);
		this->Context->SetVSync(true);
		this->Context->MakeCurrent();

		VL::RenderingAPI::Init();
		VL::Renderer::Init(this->_NewRenderer);
	}

	void WindowModule::OnDestroy()
	{

	}
	
	WindowModule::WindowModule(GraphicsAPI SelectedAPI, RendererInstance* NewRenderer)
	{
		this->_SelectedAPI = SelectedAPI;
		this->_NewRenderer = NewRenderer;
	}
}