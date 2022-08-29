#pragma once

#include "EventDispatcher/EventDispatcher.h"

struct GLFWwindow;

namespace Volund
{
    struct WindowData
    {
        uint32_t Width;
        uint32_t Height;

        Ref<EventDispatcher> Dispatcher;
    };

    enum class CursorMode
    {
        NORMAL,
        HIDDEN,
        DISABLED,
        CAPTURED
    };

    class Window
    {
    public:

        void Clear();

        void SwapBuffers();

        void PollEvents();

        bool ShouldClose();

        void MakeFullscreen();

        void SetVSync(bool Enabled);

        void SetCursorMode(CursorMode NewMode);

        Vec2 GetSize();

        GLFWwindow* GetWindowHandle();

        static void* GetProcAddress(const char* Name);

        Window(Ref<EventDispatcher>& Dispatcher);

        ~Window();

    private:

        WindowData _Data;

        GLFWwindow* _WindowHandle;
    };

} //namespace Volund