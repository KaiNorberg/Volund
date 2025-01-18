#pragma once

#include "../Component.h"

#include "Input.h"

namespace Volund
{
    class CameraMovement : public Component
    {
    public:

        float Speed = 1.0f;

        float Sensitivity = 1.0f;

        void Procedure(const Event& e);

        virtual void OnCreate();

        CameraMovement() = default;

    private:

        Input m_input;

        Vec3 m_rotation = Vec3(0.0f);

        IVec2 m_oldMousePosition = IVec2(0);
    };
} //namespace Volund
