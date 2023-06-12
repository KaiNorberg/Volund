#pragma once

#include "../Module.h"

#include "ImGuiWindow/ImGuiWindow.h"

#include "PolyContainer/PolyContainer.h"

namespace Volund
{
    class ImGuiModule : public Module
    {
    public:

        void OnAttach(Application* app) override;

        void OnDetach() override;

        void Procedure(const Event& e) override;

        template<typename T>
        void AddWindow(Ref<T> imGuiWindow);

    private:

        PolyContainer<ImGuiWindow> m_ImGuiWindows;

        bool BeginDockSpace();

        void BeginFrame();

        void EndFrame();
    };

    template<typename T>
    inline void ImGuiModule::AddWindow(Ref<T> imGuiWindow)
    {
        this->m_ImGuiWindows.PushBack(imGuiWindow);
    }
}