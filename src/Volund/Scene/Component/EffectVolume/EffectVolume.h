#pragma once

#include "Scene/Component/Component.h"
#include "Rendering/Shader/Shader.h"

namespace Volund
{
    class EffectVolume : public Component
    {
    public:

        void Procedure(const Event& e);

    private:

        std::vector<Shader> m_postEffects;
        std::vector<Shader> m_preEffects;

    };
}
