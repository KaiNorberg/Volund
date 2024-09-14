#pragma once

#include "../Renderer.h"

#define VOLUND_FORWARD_RENDERER_BINDING_CAMERA 0
#define VOLUND_FORWARD_RENDERER_BINDING_LIGHTS 1
#define VOLUND_FORWARD_RENDERER_MAX_LIGHTS 64

namespace Volund
{
    class ForwardRenderer : public Renderer
    {
    public:

        void Begin() override;

        void End() override;

        static std::shared_ptr<ForwardRenderer> Create();

    private:

        struct alignas(16) CameraBuffer
        {
            Mat4x4 ViewMatrix = Mat4x4(1.0f);
            Mat4x4 ProjectionMatrix = Mat4x4(1.0f);
        };


        struct alignas(16) LightsBuffer
        {
            uint32_t LightAmount;

            char Padding1[sizeof(Vec4) - sizeof(int)];

            Vec4 LightColors[VOLUND_FORWARD_RENDERER_MAX_LIGHTS];
            Vec4 LightPositions[VOLUND_FORWARD_RENDERER_MAX_LIGHTS];
        };

        UniformBuffer<CameraBuffer> m_CameraBuffer = UniformBuffer<CameraBuffer>(VOLUND_FORWARD_RENDERER_BINDING_CAMERA);
        UniformBuffer<LightsBuffer> m_LightsBuffer = UniformBuffer<LightsBuffer>(VOLUND_FORWARD_RENDERER_BINDING_LIGHTS);
    };
}
