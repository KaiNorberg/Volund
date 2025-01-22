#pragma once

#include "../RenderingAPI.h"
#include "../Mesh.h"

#include "../Framebuffer.h"

namespace Volund
{
    class VOLUND_API OpenGLRenderingAPI : public RenderingAPIInstance
    {
    public:
        IVec2 GetViewSize() override;
        void SetViewPort(int32_t x, int32_t y, int32_t width, int32_t height) override;
        void Clear(const RGBA color) override;
        void DrawIndexed(uint64_t indexCount) override;
        void Draw(uint64_t first, uint64_t count) override;
        void BlitFramebuffer(std::shared_ptr<Framebuffer> readBuffer, std::shared_ptr<Framebuffer> drawBuffer) override;
        OpenGLRenderingAPI();
    private:
    };
}