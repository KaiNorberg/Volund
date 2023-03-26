#pragma once

#include "../Module.h"

#include "ProgressDialog/ProgressDialog.h"
#include "TextInputDialog/TextInputDialog.h"

namespace Volund
{
    class ImGuiModule : public Module
    {
    public:

        void OnAttach(Application* app) override;

        void OnDetach() override;

        void Procedure(const Event& e) override;

        static bool BeginDockSpace();

        static void BeginFrame();

        static void EndFrame();

    private:
    };
}