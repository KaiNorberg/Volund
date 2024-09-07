#pragma once

#include "../Component.h"

namespace Volund
{
    class PointLight : public Component
    {
    public:

        RGB Color = RGB(1.0f);

        float Brightness = 1.0f;

        void Procedure(const Event& e);

        PointLight();

    private:
    };
} //namespace Volund
