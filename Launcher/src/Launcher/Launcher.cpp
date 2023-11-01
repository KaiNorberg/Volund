#include "PCH/PCH.h"
#include "Launcher.h"

void Launcher::Procedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VOLUND_EVENT_TYPE_WINDOW_CLOSE:
	{
		this->Terminate();
	}
	break;
	}
}

Launcher::Launcher()
{
	VL::RenderingAPI::Init(VL::GraphicsAPI::OpenGL);

	this->AttachModule<VL::AudioModule>();
	
	VL::FramebufferSpec spec;
	spec.ColorAttachments = { VL::TextureSpec(VL::TextureFormat::RGBA16F) };
	spec.DepthAttachment = VL::TextureSpec(VL::TextureFormat::Depth24Stencil8);
	spec.Height = 1080;
	spec.Width = 1920;

	this->m_Framebuffer = VL::Framebuffer::Create(spec);

	this->m_Renderer = VL::ForwardRenderer::Create();

	this->m_GameState = VL::GameState::Create(this->GetDispatcher());
}
