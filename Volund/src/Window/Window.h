#pragma once

#include "EventDispatcher/EventDispatcher.h"

namespace Volund
{
    struct WindowData
    {
        uint32_t Width;
        uint32_t Height;

        EventDispatcher* Dispatcher;
    };

    class VOLUND_API Window
    {
    public:

        void Clear();

        void SwapBuffers();

        void PollEvents();

        bool ShouldClose();

        void MakeFullscreen();

        void SetVSync(bool Enabled);
        
        Window(EventDispatcher* Dispatcher);

        ~Window();

    private:

        WindowData _Data;

        GLFWwindow* _WindowObject;
    };

} //namespace Volund