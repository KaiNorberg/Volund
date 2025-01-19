#include "Window.h"

#include "ImageLoader.h"

#include <GLFW/glfw3.h>

namespace Volund
{
	void DefaultWindowCloseCallback(GLFWwindow *window)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		Event e = Event(VOLUND_EVENT_CLOSE);
		windowData->EventDispatcher->Enqueue(e);
	}

	void DefaultWindowSizeCallback(GLFWwindow *window, int width, int height)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		windowData->Width = width;
		windowData->Height = height;

		Event e = Event(VOLUND_EVENT_RESIZE);
		VOLUND_EVENT_RESIZE_SET_WIDTH(e, windowData->Width);
		VOLUND_EVENT_RESIZE_SET_HEIGHT(e, windowData->Height);
		windowData->EventDispatcher->Enqueue(e);
	}

	void DefaultKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		Event e = Event(VOLUND_EVENT_KEY);
		VOLUND_EVENT_KEY_SET_KEY(e, (uint32_t)key);

		if (action == GLFW_PRESS)
		{
			VOLUND_EVENT_KEY_SET_ISDOWN(e, true);
		}
		else if (action == GLFW_RELEASE)
		{
			VOLUND_EVENT_KEY_SET_ISDOWN(e, false);
		}
		else
		{
			return;
		}

		windowData->EventDispatcher->Enqueue(e);
	}

	void DefaultCursorPositionCallback(GLFWwindow *window, double xpos, double ypos)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		Event e = Event(VOLUND_EVENT_MOUSE_MOVE);
		VOLUND_EVENT_MOUSE_MOVE_SET_XPOS(e, xpos);
		VOLUND_EVENT_MOUSE_MOVE_SET_YPOS(e, ypos);

		windowData->EventDispatcher->Enqueue(e);
	}

	void DefaultMouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		Event e = Event(VOLUND_EVENT_MOUSE_BUTTON);
		VOLUND_EVENT_MOUSE_BUTTON_SET_BUTTON(e, button);
		VOLUND_EVENT_MOUSE_BUTTON_SET_ISDOWN(e, (action != GLFW_RELEASE));

		windowData->EventDispatcher->Enqueue(e);
	}

	void DefaultScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		Event e = Event(VOLUND_EVENT_MOUSE_WHEEL);
		VOLUND_EVENT_MOUSE_WHEEL_SET_DELTA(e, (float)yoffset);

		windowData->EventDispatcher->Enqueue(e);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void WindowFocusDispatcher(GLFWwindow* window, int focused)
	{
		WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		if (windowData != nullptr)
		{
			for (auto& callback : windowData->WindowFocusCallbacks)
			{
				callback(window, focused);
			}
		}
	}

	void CursorEnterDispatcher(GLFWwindow* window, int entered)
	{
		WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		if (windowData != nullptr)
		{
			for (auto& callback : windowData->CursorEnterCallbacks)
			{
				callback(window, entered);
			}
		}
	}

	void WindowCloseDispatcher(GLFWwindow *window)
	{
		WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		if (windowData != nullptr)
		{
			for (auto& callback : windowData->WindowCloseCallbacks)
			{
				callback(window);
			}
		}
	}

	void WindowSizeDispatcher(GLFWwindow *window, int width, int height)
	{
		WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		if (windowData != nullptr)
		{
			for (auto& callback : windowData->WindowSizeCallbacks)
			{
				callback(window, width, height);
			}
		}
	}

	void KeyDispatcher(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		if (windowData != nullptr)
		{
			for (auto& callback : windowData->KeyCallbacks)
			{
				callback(window, key, scancode, action, mods);
			}
		}
	}

	void CursorPositionDispatcher(GLFWwindow *window, double xpos, double ypos)
	{
		WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		if (windowData != nullptr)
		{
			for (auto& callback : windowData->CursorPositionCallbacks)
			{
				callback(window, xpos, ypos);
			}
		}
	}

	void MouseButtonDispatcher(GLFWwindow *window, int button, int action, int mods)
	{
		WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		if (windowData != nullptr)
		{
			for (auto& callback : windowData->MouseButtonCallbacks)
			{
				callback(window, button, action, mods);
			}
		}
	}

	void ScrollDispatcher(GLFWwindow *window, double xoffset, double yoffset)
	{
		WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		if (windowData != nullptr)
		{
			for (auto& callback : windowData->ScrollCallbacks)
			{
				callback(window, xoffset, yoffset);
			}
		}
	}

	void CharDispatcher(GLFWwindow *window, unsigned int c)
	{
		WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		if (windowData != nullptr)
		{
			for (auto& callback : windowData->CharCallbacks)
			{
				callback(window, c);
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void Window::Update()
	{
		VOLUND_PROFILE_FUNCTION();

		glfwPollEvents();
	}

	GLFWwindow* Window::GetGlfwWindow()
	{
		return this->m_windowData->GlfwWindow;
	}

	void Window::SetCursorEnabled(bool enabled)
	{
		this->m_windowData->IsCursorEnabled = enabled;
		if (enabled)
		{
			glfwSetInputMode(this->m_windowData->GlfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
			glfwSetInputMode(this->m_windowData->GlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}

	bool Window::IsCursorEnabled()
	{
		return this->m_windowData->IsCursorEnabled;
	}

	void Window::SetTitle(const std::string &title)
	{
		glfwSetWindowTitle(this->m_windowData->GlfwWindow, title.c_str());
	}

	void Window::SetVsync(const bool enabled)
	{
		glfwSwapInterval(enabled);
	}

	Vec2 Window::GetSize()
	{
		return Vec2(this->m_windowData->Width, this->m_windowData->Height);
	}

	float Window::GetAspectRatio()
	{
		if (this->m_windowData->Width == 0 || this->m_windowData->Height == 0)
		{
			return 0;
		}
		else
		{
			return (float)this->m_windowData->Width / (float)this->m_windowData->Height;
		}
	}

	void Window::Flush()
	{
		VOLUND_PROFILE_FUNCTION();

		glfwSwapBuffers(this->m_windowData->GlfwWindow);
	}

	void Window::SetIcon(std::string const& filepath)
	{
		GLFWimage images[1];
		ImageLoader imageLoader = ImageLoader(filepath);
		images[0].pixels = imageLoader.GetData();
		images[0].height = imageLoader.GetHeight();
		images[0].width = imageLoader.GetWidth();

		glfwSetWindowIcon(this->m_windowData->GlfwWindow, 1, images);
	}

    void Window::ConnectWindowFocusCallback(GLFWwindowfocusfun callback)
    {
		this->m_windowData->WindowFocusCallbacks.push_back(callback);
    }

    void Window::ConnectCursorEnterCallback(GLFWcursorenterfun callback)
    {
		this->m_windowData->CursorEnterCallbacks.push_back(callback);
    }

    void Window::ConnectWindowCloseCallback(GLFWwindowclosefun callback)
    {
		this->m_windowData->WindowCloseCallbacks.push_back(callback);
    }

    void Window::ConnectWindowSizeCallback(GLFWwindowsizefun callback)
    {
		this->m_windowData->WindowSizeCallbacks.push_back(callback);
    }

    void Window::ConnectKeyCallback(GLFWkeyfun callback)
    {
		this->m_windowData->KeyCallbacks.push_back(callback);
    }

    void Window::ConnectCursorPositionCallback(GLFWcursorposfun callback)
    {
		this->m_windowData->CursorPositionCallbacks.push_back(callback);
    }

    void Window::ConnectMouseButtonCallback(GLFWmousebuttonfun callback)
    {
		this->m_windowData->MouseButtonCallbacks.push_back(callback);
    }

    void Window::ConnectScrollCallback(GLFWscrollfun callback)
    {
		this->m_windowData->ScrollCallbacks.push_back(callback);
    }

    void Window::ConnectCharCallback(GLFWcharfun callback)
    {
		this->m_windowData->CharCallbacks.push_back(callback);
    }

    Window::Window(std::shared_ptr<Dispatcher> Dispatcher, uint64_t Width, uint64_t Height, bool FullScreen)
	{
		VOLUND_INFO("Creating window...");

		this->m_windowData = std::make_shared<WindowData>();
		this->m_windowData->EventDispatcher = Dispatcher;

		if (!glfwInit())
		{
			VOLUND_ERROR("Failed to init glfw!");
		}

		if (FullScreen)
		{
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();

			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

			GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "Volund", monitor, 0);
			this->m_windowData->Height = mode->height;
			this->m_windowData->Width = mode->width;
		}
		else
		{
			this->m_windowData->GlfwWindow = glfwCreateWindow(Width, Height, "Volund", 0, 0);

			this->m_windowData->Height = Height;
			this->m_windowData->Width = Width;
		}

		if (!this->m_windowData->GlfwWindow)
		{
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(this->m_windowData->GlfwWindow);

		glfwSetWindowUserPointer(this->m_windowData->GlfwWindow, this->m_windowData.get());

		glfwSetWindowFocusCallback(this->m_windowData->GlfwWindow, WindowFocusDispatcher);
		glfwSetCursorEnterCallback(this->m_windowData->GlfwWindow, CursorEnterDispatcher);
		glfwSetWindowCloseCallback(this->m_windowData->GlfwWindow, WindowCloseDispatcher);
		glfwSetFramebufferSizeCallback(this->m_windowData->GlfwWindow, WindowSizeDispatcher);
		glfwSetKeyCallback(this->m_windowData->GlfwWindow, KeyDispatcher);
		glfwSetCursorPosCallback(this->m_windowData->GlfwWindow, CursorPositionDispatcher);
		glfwSetMouseButtonCallback(this->m_windowData->GlfwWindow, MouseButtonDispatcher);
		glfwSetScrollCallback(this->m_windowData->GlfwWindow, ScrollDispatcher);
		glfwSetCharCallback(this->m_windowData->GlfwWindow, CharDispatcher);

		this->ConnectWindowCloseCallback(DefaultWindowCloseCallback);
		this->ConnectWindowSizeCallback(DefaultWindowSizeCallback);
		this->ConnectKeyCallback(DefaultKeyCallback);
		this->ConnectCursorPositionCallback(DefaultCursorPositionCallback);
		this->ConnectMouseButtonCallback(DefaultMouseButtonCallback);
		this->ConnectScrollCallback(DefaultScrollCallback);

		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

		this->SetVsync(true);
	}

	Window::~Window()
	{
		glfwDestroyWindow(this->m_windowData->GlfwWindow);
		glfwTerminate();
	}

} // namespace Volund
