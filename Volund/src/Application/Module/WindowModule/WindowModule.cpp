#include "PCH/PCH.h"
#include "WindowModule.h"

#include "Application/Application.h"

namespace Volund
{
	Ref<Window> WindowModule::GetWindow()
	{
		return this->m_Window;
	}

	void WindowModule::OnAttach(Application* app)
	{
		this->m_Window = std::make_shared<Window>(app->GetEventDispatcher(), 1980, 1080, false);

		this->m_Window->SetTitle("Volund");

		VL::RenderingAPI::Init();
		VL::Renderer::Init(this->m_RendererInstance);

		//VOLUND_INFO("OpenGL Renderer: %s", glGetString(GL_RENDERER));
		//VOLUND_INFO("OpenGL Version: %s", glGetString(GL_VERSION));
		//VOLUND_INFO("OpenGL Vendor: %s", glGetString(GL_VENDOR));		
	}

	void WindowModule::OnDetach()
	{
	}

	void WindowModule::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (e.Type)
		{
		case EventType::Render:
		{
			this->m_Window->Flush();
			this->m_Window->Update();
		}
		break;
		default:
		{

		}
		break;
		}
	}

	WindowModule::WindowModule(GraphicsAPI api, Ref<RendererInstance> instance)
	{
		VL::RenderingAPI::Select(api);
		this->m_RendererInstance = instance;
	}
}