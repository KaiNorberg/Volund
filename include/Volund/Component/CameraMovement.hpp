#pragma once

#include "Component.hpp"
#include "../Input.hpp"
#include "../Math.hpp"

namespace Volund
{
    class VOLUND_API CameraMovement : public Component
    {
    public:
        float speed;
        float sensitivity;
        void Procedure(const Event& e);
        CameraMovement(float speed = 1.0f, float sensitivity = 1.0f);
    private:
        Input m_input;
        Vec3 m_rotation = Vec3(0.0f);
        IVec2 m_oldMousePosition = IVec2(0);
    };
} //namespace Volund