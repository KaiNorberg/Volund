#pragma once

#include "Component.h"

namespace Volund
{
    class PointLight : public Component
    {
    public:
        RGB color;
        float brightness ;
        void Procedure(const Event& e);
        PointLight(const RGB& color = RGB(1.0f), float brighness = 500.0f);
    private:
    };
} //namespace Volund