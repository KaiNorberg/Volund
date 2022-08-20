#pragma once

struct GLFWwindow;

namespace Volund
{
    class VOLUND_API Window
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