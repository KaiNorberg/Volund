#pragma once

#include "../Module.h"

#include "ProgressDialog/ProgressDialog.h"
#include "TextInputDialog/TextInputDialog.h"

namespace Volund
{
    class ImGuiModule : public Module
    {
    public:

        void OnEvent(Event* E) override;

        void OnUpdate(TimeStep TS) override;

        void OnAttach(Application* App) override;

        void OnDestroy() override;   

        static bool BeginDockSpace();

        static void BeginFrame();

        static void EndFrame();

    private:
    };
}