#pragma once

#include "../Module.h"

#include "ProgressDialog/ProgressDialog.h"
#include "TextInputDialog/TextInputDialog.h"

namespace Volund
{
    class ImGuiModule : public Module
    {
    public:

        void OnAttach(Application* App) override;

        void OnDetach() override;

        void Procedure(const Event& E) override;

        static bool BeginDockSpace();

        static void BeginFrame();

        static void EndFrame();

    private:
    };
}