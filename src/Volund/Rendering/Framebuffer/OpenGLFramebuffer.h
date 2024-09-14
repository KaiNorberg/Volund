#pragma once

#include "Framebuffer.h"

namespace Volund
{
    class OpenGLFramebuffer : public Framebuffer
    {
    public:

        uint32_t GetID() const override;

        void Bind() override;

        void Unbind() override;

        void Invalidate() override;

        void BlitTo(const std::shared_ptr<Framebuffer>& drawFramebuffer) override;

        void BlitToScreen() override;

        uint32_t GetAttachment(uint32_t index) override;

        uint32_t GetDepthAttachment() override;

        void SetSpec(const FramebufferSpec& spec) override;

        const FramebufferSpec GetSpec() const override;

        OpenGLFramebuffer(const FramebufferSpec& spec);

        ~OpenGLFramebuffer();

    private:

        uint32_t m_Id;

        FramebufferSpec m_Spec;

        std::vector<uint32_t> m_ColorAttachments;

        uint32_t m_DepthAttachment = 0;
    };
}
