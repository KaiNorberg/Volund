#pragma once

#include "Component.hpp"

#include "../Audio/AudioListener.hpp"

namespace Volund
{
    class VOLUND_API SoundListener : public Component
    {
    public:
        void Procedure(const Event& e);
        SoundListener() = default;
    private:
        AudioListener m_listener;
    };
}