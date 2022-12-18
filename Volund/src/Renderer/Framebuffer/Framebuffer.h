#pragma once

#include "Renderer/TextureSpec/TextureSpec.h"

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

		virtual void BlitTo(const Ref<Framebuffer>& DrawFramebuffer) = 0;

		uint32_t GetID();

		uint32_t GetAttachment(uint32_t Index);

		uint32_t GetDepthAttachment();

		void SetSpec(const FramebufferSpec& Spec);

		const FramebufferSpec GetSpec() const;

		static Ref<Framebuffer> Create(const FramebufferSpec& Spec);

		virtual ~Framebuffer() = default;

	protected:

		uint32_t _ID;

		FramebufferSpec _Spec;		
		
		std::vector<uint32_t> _ColorAttachments;

		uint32_t _DepthAttachment = NULL;
	};
}
