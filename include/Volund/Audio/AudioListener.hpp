#pragma once

#include "../Math.hpp"
#include "AudioBuffer.hpp"

#include <cstdint>

namespace Volund
{
    class VOLUND_API AudioListener
    {
    public:
        void SetPosition(const Vec3& position);
        void SetOrientation(const Vec3& front, const Vec3& up);
        void SetVelocity(const Vec3& velocity);
        AudioListener();
        ~AudioListener();
    private:
        static inline uint32_t m_audioListenerCount = 0;
    };
}