#include "PCH/PCH.h"
#include "LuaFramebuffer.h"

namespace Volund
{
	Ref<Framebuffer> LuaFramebuffer::Get()
	{
		return this->m_Framebuffer;
	}

	void LuaFramebuffer::Resize(LuaVec2 newSize)
	{
		auto spec = this->m_Framebuffer->GetSpec();
		spec.Width = newSize.x;
		spec.Height = newSize.y;
		this->m_Framebuffer->SetSpec(spec);
	}

	LuaVec2 LuaFramebuffer::GetSize()
	{
		return LuaVec2(this->m_Framebuffer->GetSpec().Width, this->m_Framebuffer->GetSpec().Height);
	}

	LuaFramebuffer::LuaFramebuffer(const LuaVec2& size)
	{
		VL::FramebufferSpec spec;
		spec.ColorAttachments = { VL::TextureSpec(VL::TextureFormat::RGBA16F) };
		spec.DepthAttachment = VL::TextureSpec(VL::TextureFormat::Depth24Stencil8);
		spec.Height = size.x;
		spec.Width = size.y;
		this->m_Framebuffer = Framebuffer::Create(spec);
	}

	LuaFramebuffer::LuaFramebuffer(Ref<Framebuffer> framebuffer)
	{
		this->m_Framebuffer = framebuffer;
	}
}