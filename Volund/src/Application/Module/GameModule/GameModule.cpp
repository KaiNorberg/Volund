#include "PCH/PCH.h"
#include "GameModule.h"

#include "Application/Application.h"

namespace Volund
{
	void GameModule::OnAttach(Application* app)
	{
		this->m_GameWindow = app->GetWindow();
		this->m_Dispatcher = app->GetDispatcher();

		this->m_Renderer = std::make_shared<ForwardRenderer>();

		VL::FramebufferSpec spec;
		spec.ColorAttachments = { VL::TextureSpec(VL::TextureFormat::RGBA16F) };
		spec.DepthAttachment = VL::TextureSpec(VL::TextureFormat::Depth24Stencil8);
		spec.Height = 1080;
		spec.Width = 1920;
		this->m_Framebuffer = VL::Framebuffer::Create(spec);
	}

	void GameModule::OnDetach()
	{

	}

	void GameModule::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		if (this->m_GameState == nullptr)
		{
			return;
		}

		this->m_GameState->Procedure(e);

		switch (e.Type)
		{
		case VOLUND_EVENT_TYPE_RENDER:
		{
			auto scene = this->m_GameState->GetScene();

			if (this->m_GameState->GetScene() != nullptr)
			{
				this->m_Renderer->Begin(this->m_Framebuffer);
				this->m_Renderer->Submit(scene);
				this->m_Renderer->End();
				RenderingAPI::BlitFramebuffer(this->m_Framebuffer, nullptr);
			}
		}
		break;
		case VOLUND_EVENT_TYPE_WINDOW_SIZE:
		{
			uint32_t width = VOLUND_EVENT_WINDOW_SIZE_GET_WIDTH(e);
			uint32_t height = VOLUND_EVENT_WINDOW_SIZE_GET_HEIGHT(e);

			auto spec = this->m_Framebuffer->GetSpec();
			spec.Height = height;
			spec.Width = width;
			this->m_Framebuffer->SetSpec(spec);
		}
		break;
		}
	}

	std::string GameModule::GetFilepath()
	{
		return this->m_Filepath;
	}

	Ref<Scene> GameModule::GetScene()
	{
		if (this->m_GameState != nullptr)
		{
			return this->m_GameState->GetScene();
		}
		else
		{
			return nullptr;
		}
	}

	Ref<Window> GameModule::GetWindow()
	{
		return this->m_GameWindow;
	}

	void GameModule::LoadScene(const std::string& filepath)
	{
		std::unique_lock lock(this->m_Mutex);

		this->m_Filepath = filepath;

		this->m_GameState.reset();

		this->m_GameState = std::make_shared<VL::GameState>(this->m_Dispatcher, this->m_Filepath);
	}
}