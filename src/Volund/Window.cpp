#include "Window.h"

#include "ImageLoader.h"

#include <GLFW/glfw3.h>

namespace Volund
{
	void DefaultWindowCloseCallback(GLFWwindow *window)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		Event e = Event(VOLUND_EVENT_CLOSE);
		windowData->dispatcher->Enqueue(e);
	}

	void DefaultWindowSizeCallback(GLFWwindow *window, int width, int height)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		windowData->width = width;
		windowData->height = height;

		Event e = Event(VOLUND_EVENT_RESIZE);
		VOLUND_EVENT_RESIZE_SET_WIDTH(e, windowData->width);
		VOLUND_EVENT_RESIZE_SET_HEIGHT(e, windowData->height);
		windowData->dispatcher->Enqueue(e);
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

		windowData->dispatcher->Enqueue(e);
	}

	void DefaultCursorPositionCallback(GLFWwindow *window, double xpos, double ypos)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		Event e = Event(VOLUND_EVENT_MOUSE_MOVE);
		VOLUND_EVENT_MOUSE_MOVE_SET_XPOS(e, xpos);
		VOLUND_EVENT_MOUSE_MOVE_SET_YPOS(e, ypos);

		windowData->dispatcher->Enqueue(e);
	}

	void DefaultMouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		Event e = Event(VOLUND_EVENT_MOUSE_BUTTON);
		VOLUND_EVENT_MOUSE_BUTTON_SET_BUTTON(e, button);
		VOLUND_EVENT_MOUSE_BUTTON_SET_ISDOWN(e, (action != GLFW_RELEASE));

		windowData->dispatcher->Enqueue(e);
	}

	void DefaultScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		Event e = Event(VOLUND_EVENT_MOUSE_WHEEL);
		VOLUND_EVENT_MOUSE_WHEEL_SET_DELTA(e, (float)yoffset);

		windowData->dispatcher->Enqueue(e);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void WindowFocusDispatcher(GLFWwindow* window, int focused)
	{
		WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		if (windowData != nullptr)
		{
			for (auto& callback : windowData->windowFocusCallbacks)
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
			for (auto& callback : windowData->cursorEnterCallbacks)
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
			for (auto& callback : windowData->windowCloseCallbacks)
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
			for (auto& callback : windowData->windowSizeCallbacks)
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
			for (auto& callback : windowData->keyCallbacks)
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
			for (auto& callback : windowData->cursorPositionCallbacks)
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
			for (auto& callback : windowData->mouseButtonCallbacks)
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
			for (auto& callback : windowData->scrollCallbacks)
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
			for (auto& callback : windowData->charCallbacks)
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
		return this->m_windowData->glfwWindow;
	}

	void Window::SetCursorEnabled(bool enabled)
	{
		this->m_windowData->isCursorEnabled = enabled;
		if (enabled)
		{
			glfwSetInputMode(this->m_windowData->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
			glfwSetInputMode(this->m_windowData->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}

	bool Window::IsCursorEnabled()
	{
		return this->m_windowData->isCursorEnabled;
	}

	void Window::SetTitle(const std::string &title)
	{
		glfwSetWindowTitle(this->m_windowData->glfwWindow, title.c_str());
	}

	void Window::SetVsync(const bool enabled)
	{
		glfwSwapInterval(enabled);
	}

	uint64_t Window::GetWidth()
	{
		return this->m_windowData->width;
	}

	uint64_t Window::GetHeight()
	{
		return this->m_windowData->height;
	}

	float Window::GetAspectRatio()
	{
		if (this->m_windowData->width == 0 || this->m_windowData->height == 0)
		{
			return 0;
		}
		else
		{
			return (float)this->m_windowData->width / (float)this->m_windowData->height;
		}
	}

	void Window::Flush()
	{
		VOLUND_PROFILE_FUNCTION();

		glfwSwapBuffers(this->m_windowData->glfwWindow);
	}

	void Window::SetIcon(std::string const& filepath)
	{
		GLFWimage images[1];
		ImageLoader imageLoader = ImageLoader(filepath, false);
		images[0].pixels = imageLoader.GetData();
		images[0].height = imageLoader.GetHeight();
		images[0].width = imageLoader.GetWidth();

		glfwSetWindowIcon(this->m_windowData->glfwWindow, 1, images);
	}

    void Window::ConnectWindowFocusCallback(GLFWwindowfocusfun callback)
    {
		this->m_windowData->windowFocusCallbacks.push_back(callback);
    }

    void Window::ConnectCursorEnterCallback(GLFWcursorenterfun callback)
    {
		this->m_windowData->cursorEnterCallbacks.push_back(callback);
    }

    void Window::ConnectWindowCloseCallback(GLFWwindowclosefun callback)
    {
		this->m_windowData->windowCloseCallbacks.push_back(callback);
    }

    void Window::ConnectWindowSizeCallback(GLFWwindowsizefun callback)
    {
		this->m_windowData->windowSizeCallbacks.push_back(callback);
    }

    void Window::ConnectKeyCallback(GLFWkeyfun callback)
    {
		this->m_windowData->keyCallbacks.push_back(callback);
    }

    void Window::ConnectCursorPositionCallback(GLFWcursorposfun callback)
    {
		this->m_windowData->cursorPositionCallbacks.push_back(callback);
    }

    void Window::ConnectMouseButtonCallback(GLFWmousebuttonfun callback)
    {
		this->m_windowData->mouseButtonCallbacks.push_back(callback);
    }

    void Window::ConnectScrollCallback(GLFWscrollfun callback)
    {
		this->m_windowData->scrollCallbacks.push_back(callback);
    }

    void Window::ConnectCharCallback(GLFWcharfun callback)
    {
		this->m_windowData->charCallbacks.push_back(callback);
    }

    Window::Window(std::shared_ptr<Dispatcher> dispatcher, uint64_t width, uint64_t height, bool fullScreen)
	{
		VOLUND_INFO("Creating window {}x{}", width, height);

		this->m_windowData = std::make_shared<WindowData>();
		this->m_windowData->dispatcher = dispatcher;

		if (!glfwInit())
		{
			VOLUND_ERROR("Failed to create window - glfwInit() returned false");
		}

		if (fullScreen)
		{
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();

			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

			GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "Volund", monitor, 0);
			this->m_windowData->height = mode->height;
			this->m_windowData->width = mode->width;
		}
		else
		{
			this->m_windowData->glfwWindow = glfwCreateWindow(width, height, "Volund", 0, 0);

			this->m_windowData->height = height;
			this->m_windowData->width = width;
		}

		if (!this->m_windowData->glfwWindow)
		{
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(this->m_windowData->glfwWindow);

		glfwSetWindowUserPointer(this->m_windowData->glfwWindow, this->m_windowData.get());

		glfwSetWindowFocusCallback(this->m_windowData->glfwWindow, WindowFocusDispatcher);
		glfwSetCursorEnterCallback(this->m_windowData->glfwWindow, CursorEnterDispatcher);
		glfwSetWindowCloseCallback(this->m_windowData->glfwWindow, WindowCloseDispatcher);
		glfwSetFramebufferSizeCallback(this->m_windowData->glfwWindow, WindowSizeDispatcher);
		glfwSetKeyCallback(this->m_windowData->glfwWindow, KeyDispatcher);
		glfwSetCursorPosCallback(this->m_windowData->glfwWindow, CursorPositionDispatcher);
		glfwSetMouseButtonCallback(this->m_windowData->glfwWindow, MouseButtonDispatcher);
		glfwSetScrollCallback(this->m_windowData->glfwWindow, ScrollDispatcher);
		glfwSetCharCallback(this->m_windowData->glfwWindow, CharDispatcher);

		this->ConnectWindowCloseCallback(DefaultWindowCloseCallback);
		this->ConnectWindowSizeCallback(DefaultWindowSizeCallback);
		this->ConnectKeyCallback(DefaultKeyCallback);
		this->ConnectCursorPositionCallback(DefaultCursorPositionCallback);
		this->ConnectMouseButtonCallback(DefaultMouseButtonCallback);
		this->ConnectScrollCallback(DefaultScrollCallback);

		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

		this->SetVsync(true);

		VOLUND_INFO("Successfully created window");
	}

	Window::~Window()
	{
		glfwDestroyWindow(this->m_windowData->glfwWindow);
		glfwTerminate();
	}

} // namespace Volund
