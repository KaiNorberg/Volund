#pragma once

#include "../Module.h"

#include "Audio/AudioDevice/AudioDevice.h"
#include "Audio/AudioContext/AudioContext.h"

namespace Volund
{
    class AudioModule : public Module
    {
    public:

        void OnAttach(Application* app) override;

        void OnDetach() override;

        void Procedure(const Event& e) override;

    private:

        std::shared_ptr<AudioDevice> m_device;
        std::shared_ptr<AudioContext> m_context;
    };
}
