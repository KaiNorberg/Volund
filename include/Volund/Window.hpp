#pragma once

#include "Dispatcher.hpp"

#include "Rendering/Framebuffer.hpp"

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
        uint64_t width = 0;
        uint64_t height = 0;
        GLFWwindow* glfwWindow = nullptr;
        bool isCursorEnabled = true;
        std::shared_ptr<Dispatcher> dispatcher;
        std::vector<GLFWwindowfocusfun> windowFocusCallbacks;
        std::vector<GLFWcursorenterfun> cursorEnterCallbacks;
        std::vector<GLFWwindowclosefun> windowCloseCallbacks;
        std::vector<GLFWwindowsizefun> windowSizeCallbacks;
        std::vector<GLFWkeyfun> keyCallbacks;
        std::vector<GLFWcursorposfun> cursorPositionCallbacks;
        std::vector<GLFWmousebuttonfun> mouseButtonCallbacks;
        std::vector<GLFWscrollfun> scrollCallbacks;
        std::vector<GLFWcharfun> charCallbacks;
    };

    class VOLUND_API Window
    {
    public:
        void Update();
        GLFWwindow* GetGlfwWindow();
        void SetCursorEnabled(bool enabled);
        bool IsCursorEnabled();
        void SetTitle(std::string const& title);
        void SetVsync(bool enabled);
        uint64_t GetWidth();
        uint64_t GetHeight();
        float GetAspectRatio();
        void Flush();
        void SetIcon(std::string const& filepath);
        void ConnectWindowFocusCallback(GLFWwindowfocusfun callback);
        void ConnectCursorEnterCallback(GLFWcursorenterfun callback);
        void ConnectWindowCloseCallback(GLFWwindowclosefun callback);
        void ConnectWindowSizeCallback(GLFWwindowsizefun callback);
        void ConnectKeyCallback(GLFWkeyfun callback);
        void ConnectCursorPositionCallback(GLFWcursorposfun callback);
        void ConnectMouseButtonCallback(GLFWmousebuttonfun callback);
        void ConnectScrollCallback(GLFWscrollfun callback);
        void ConnectCharCallback(GLFWcharfun callback);
        Window(std::shared_ptr<Dispatcher> dispatcher, uint64_t width, uint64_t height, bool fullScreen);
        ~Window();
    private:
        std::shared_ptr<WindowData> m_windowData;
    };
}
