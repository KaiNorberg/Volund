#pragma once

#include "Component.h"
#include "../Rendering/Framebuffer.h"

namespace Volund
{
    class Camera : public Component
    {
    public:
        float fov;
        float nearPlane;
        float farPlane;
        void SetLayerMask(uint8_t index, bool enabled);
        uint32_t GetLayerMask();
        Mat4x4 GetViewMatrix() const;
        Mat4x4 GetOriginViewMatrix() const;
        Mat4x4 GetProjectionMatrix(const float aspectRatio) const;
        void Procedure(const Event& e);
        Camera(float fov = 80.0f, float nearPlane = 0.0f, float farPlane = 100.0f);
    private:
        uint32_t m_layerMask = std::numeric_limits<uint32_t>::max();
    };
}