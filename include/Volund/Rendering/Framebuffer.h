#pragma once

#include "TextureSpec.h"

#include <vector>
#include <cstdint>
#include <memory>

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

        virtual uint32_t GetID() const = 0;

        virtual void Bind() = 0;

        virtual void Unbind() = 0;

        virtual void Invalidate() = 0;

        virtual void BlitTo(const std::shared_ptr<Framebuffer>& drawFramebuffer) = 0;

        virtual void BlitToScreen() = 0;

        virtual uint32_t GetAttachment(uint32_t index) = 0;

        virtual uint32_t GetDepthAttachment() = 0;

        virtual void SetSpec(const FramebufferSpec& spec) = 0;

        virtual const FramebufferSpec GetSpec() const = 0;

        static std::shared_ptr<Framebuffer> Create(const FramebufferSpec& spec);

        virtual ~Framebuffer() = default;
    };
}