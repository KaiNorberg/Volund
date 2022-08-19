#pragma once

#include "Math/Math.h"

namespace Volund
{
    class Window
    {
    public:

        void Clear();

        void SwapBuffers();

        void PollEvents();

        bool ShouldClose();

        void MakeFullscreen();

        Window();

        ~Window();

    private:

        GLFWwindow* WindowObject;

    };

} //namespace Volund