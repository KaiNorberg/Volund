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

        void SetBackgroundCallback(std::function<void()> callback);
          
        template<typename T, typename... Args>
        Ref<T> CreateWindow(Args&&... args);

    private:

        bool BeginDockSpace();

        void BeginFrame();

        void EndFrame();

        std::function<void()> m_BackgroundCallback;

        PolyContainer<ImGuiWindow> m_ImGuiWindows;
    };

    template<typename T, typename ...Args>
    inline Ref<T> ImGuiModule::CreateWindow(Args&&... args)
    {
        Ref<T> newWindow = std::make_shared<T>(args...);
        this->m_ImGuiWindows.PushBack(newWindow);

        return newWindow;
    }
}