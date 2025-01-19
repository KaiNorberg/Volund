#pragma once

#include "Component.h"

#include "../Audio/AudioListener.h"

namespace Volund
{
    class SoundListener : public Component
    {
    public:
        void Procedure(const Event& e);
        SoundListener() = default;
    private:
        AudioListener m_listener;
    };
}