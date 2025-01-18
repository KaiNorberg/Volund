#pragma once

#include "../Component.h"
#include "Rendering/Framebuffer/Framebuffer.h"

namespace Volund
{
    class Camera : public Component
    {
    public:

        float FOV = 80.0f;

        float NearPlane = 0.1f;

        float FarPlane = 100.0f;

        void SetLayerMask(uint8_t index, bool enabled);

        uint32_t GetLayerMask();

        Mat4x4 GetViewMatrix() const;

        Mat4x4 GetOriginViewMatrix() const;

        Mat4x4 GetProjectionMatrix(const float aspectRatio) const;

        void Procedure(const Event& e);

        void OnCreate() override;

        Camera() = default;

    private:

        uint32_t m_layerMask = std::numeric_limits<uint32_t>::max();
    };
}
