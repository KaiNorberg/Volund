#pragma once

#include "Rendering/TextureSpec/TextureSpec.h"

namespace Volund
{
	struct FramebufferSpec
	{
		uint32_t Width = 0;
		uint32_t Height = 0;
		uint32_t Samples = 1;

		std::vector<TextureSpec> ColorAttachments;
		TextureSpec DepthAttachment = {};

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:

		virtual void Bind() = 0;
		
		virtual void Unbind() = 0;

		virtual void Invalidate() = 0;

		virtual void BlitTo(const Ref<Framebuffer>& drawFramebuffer) = 0;

		uint32_t GetID() const;

		uint32_t GetAttachment(uint32_t index);

		uint32_t GetDepthAttachment();

		void SetSpec(const FramebufferSpec& spec);

		const FramebufferSpec GetSpec() const;

		static Ref<Framebuffer> Create(const FramebufferSpec& spec);

		virtual ~Framebuffer() = default;

	protected:

		uint32_t m_Id;

		FramebufferSpec m_Spec;		
		
		std::vector<uint32_t> m_ColorAttachments;

		uint32_t m_DepthAttachment = 0;
	};
}
