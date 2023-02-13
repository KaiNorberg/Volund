#include "PCH/PCH.h"
#include "WindowModule.h"

#include "Application/Application.h"

#include "glad/glad.h"

namespace Volund
{
	Ref<Window> WindowModule::GetWindow()
	{
		return this->_Window;
	}

	void WindowModule::OnAttach(Application* App)
	{
		this->_Window = std::make_shared<Window>(App->GetEventDispatcher(), 1980, 1080, false);

		this->_Window->SetTitle("Volund");
		this->_Window->SetFocus();

		this->_Window->Show();

		VL::RenderingAPI::Init();
		VL::Renderer::Init(this->_RendererInstance);

		VOLUND_INFO("OpenGL Renderer: %s", glGetString(GL_RENDERER));
		VOLUND_INFO("OpenGL Version: %s", glGetString(GL_VERSION));
		VOLUND_INFO("OpenGL Vendor: %s", glGetString(GL_VENDOR));		
	}

	void WindowModule::OnDetach()
	{
	}

	void WindowModule::Procedure(const Event& E)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (E.Type)
		{
		case EventType::RENDER:
		{
			this->_Window->Update();
			this->_Window->Flush();
		}
		break;
		default:
		{

		}
		break;
		}
	}

	WindowModule::WindowModule(GraphicsAPI API, Ref<RendererInstance> Instance)
	{
		VL::RenderingAPI::Select(VL::GraphicsAPI::OPENGL);
		this->_RendererInstance = Instance;
	}
}