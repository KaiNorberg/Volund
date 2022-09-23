#pragma once

namespace Volund
{
	struct FramebufferSpec
	{
		uint32_t Width = 0;
		uint32_t Height = 0;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:

		virtual void Bind() = 0;
		
		virtual void Unbind() = 0;

		virtual void Invalidate() = 0;

		virtual uint32_t GetColorAttachment() = 0;

		void SetSpec(const FramebufferSpec& Spec);

		const FramebufferSpec GetSpec() const;

		static Ref<Framebuffer> Create(const FramebufferSpec& Spec);

		virtual ~Framebuffer() = default;

	protected:
	
		FramebufferSpec _Spec;
	};
}
