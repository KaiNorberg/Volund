#pragma once

#include "Dispatcher/Dispatcher.h"

#include "Rendering/Framebuffer/Framebuffer.h"

struct GLFWwindow;
typedef void (*GLFWwindowfocusfun)(GLFWwindow* window, int focused);
typedef void (*GLFWcursorenterfun)(GLFWwindow* window, int entered);
typedef void (*GLFWwindowclosefun)(GLFWwindow* window);
typedef void (*GLFWwindowsizefun)(GLFWwindow* window, int width, int height);
typedef void (*GLFWkeyfun)(GLFWwindow* window, int key, int scancode, int action, int mods);
typedef void (*GLFWcursorposfun)(GLFWwindow* window, double xpos, double ypos);
typedef void (*GLFWmousebuttonfun)(GLFWwindow* window, int button, int action, int mods);
typedef void (*GLFWscrollfun)(GLFWwindow* window, double xoffset, double yoffset);
typedef void (*GLFWcharfun)(GLFWwindow* window, unsigned int codepoint);

namespace Volund
{
    struct WindowData
    {
        uint64_t Width = 0;
        uint64_t Height = 0;

        GLFWwindow* GlfwWindow = nullptr;

        bool IsCursorEnabled = true;

        std::shared_ptr<Dispatcher> EventDispatcher;

        std::vector<GLFWwindowfocusfun> WindowFocusCallbacks;
        std::vector<GLFWcursorenterfun> CursorEnterCallbacks;
        std::vector<GLFWwindowclosefun> WindowCloseCallbacks;
        std::vector<GLFWwindowsizefun> WindowSizeCallbacks;
        std::vector<GLFWkeyfun> KeyCallbacks;
        std::vector<GLFWcursorposfun> CursorPositionCallbacks;
        std::vector<GLFWmousebuttonfun> MouseButtonCallbacks;
        std::vector<GLFWscrollfun> ScrollCallbacks;
        std::vector<GLFWcharfun> CharCallbacks;
    };

    class Window
    {
    public:

        void Update();

        GLFWwindow* GetGlfwWindow();

        void SetCursorEnabled(bool enabled);

        bool IsCursorEnabled();

        void SetTitle(const std::string& title);

        void SetVsync(bool enabled);

        Vec2 GetSize();

        float GetAspectRatio();

        void Flush();

        void SetIcon(const std::string& filepath);

        void ConnectWindowFocusCallback(GLFWwindowfocusfun callback);
        void ConnectCursorEnterCallback(GLFWcursorenterfun callback);
        void ConnectWindowCloseCallback(GLFWwindowclosefun callback);
        void ConnectWindowSizeCallback(GLFWwindowsizefun callback);
        void ConnectKeyCallback(GLFWkeyfun callback);
        void ConnectCursorPositionCallback(GLFWcursorposfun callback);
        void ConnectMouseButtonCallback(GLFWmousebuttonfun callback);
        void ConnectScrollCallback(GLFWscrollfun callback);
        void ConnectCharCallback(GLFWcharfun callback);

        Window(std::shared_ptr<Dispatcher> Dispatcher, uint64_t width, uint64_t height, bool fullScreen);

        ~Window();

    private:

        std::shared_ptr<WindowData> m_WindowData;
    };
}
