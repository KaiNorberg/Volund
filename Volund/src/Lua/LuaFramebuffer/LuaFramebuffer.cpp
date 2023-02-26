#include "PCH/PCH.h"
#include "LuaFramebuffer.h"

namespace Volund
{
	Ref<Framebuffer> LuaFramebuffer::Get()
	{
		return this->_Framebuffer;
	}

	void LuaFramebuffer::Resize(LuaVec2 NewSize)
	{
		auto Spec = this->_Framebuffer->GetSpec();
		Spec.Width = NewSize.x;
		Spec.Height = NewSize.y;
		this->_Framebuffer->SetSpec(Spec);
	}

	LuaVec2 LuaFramebuffer::GetSize()
	{
		return LuaVec2(this->_Framebuffer->GetSpec().Width, this->_Framebuffer->GetSpec().Height);
	}

	LuaFramebuffer::LuaFramebuffer(const LuaVec2& Size)
	{
		VL::FramebufferSpec Spec;
		Spec.ColorAttachments = { VL::TextureSpec(VL::TextureFormat::RGBA16F) };
		Spec.DepthAttachment = VL::TextureSpec(VL::TextureFormat::DEPTH24STENCIL8);
		Spec.Height = Size.x;
		Spec.Width = Size.y;
		this->_Framebuffer = Framebuffer::Create(Spec);
	}

	LuaFramebuffer::LuaFramebuffer(Ref<Framebuffer> RawFramebuffer)
	{
		this->_Framebuffer = RawFramebuffer;
	}
}