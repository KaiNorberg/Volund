#pragma once

#include "../Module.hpp"

#include "AudioDevice.hpp"
#include "AudioContext.hpp"

namespace Volund
{
    class VOLUND_API AudioModule : public Module
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