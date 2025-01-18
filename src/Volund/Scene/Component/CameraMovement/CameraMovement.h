#pragma once

#include "../Component.h"

#include "Input.h"

namespace Volund
{
    class CameraMovement : public Component
    {
    public:

        float speed;

        float sensitivity;

        void Procedure(const Event& e);

        virtual void OnCreate();

        CameraMovement(float speed = 1.0f, float sensitivity = 1.0f);

    private:

        Input m_input;

        Vec3 m_rotation = Vec3(0.0f);

        IVec2 m_oldMousePosition = IVec2(0);
    };
} //namespace Volund
