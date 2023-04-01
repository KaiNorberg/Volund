#include "PCH/PCH.h"
#include "Window.h"

namespace Volund
{
	void DefaultWindowCloseCallback(GLFWwindow *window)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		Event e = Event(EventType::WindowClose);
		windowData->Dispatcher->Dispatch(e);
	}

	void DefaultWindowSizeCallback(GLFWwindow *window, int width, int height)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		Event e = Event(EventType::WindowSize);
		VOLUND_EVENT_WINDOW_SIZE_SET_WIDTH(e, windowData->Width);
		VOLUND_EVENT_WINDOW_SIZE_SET_HEIGHT(e, windowData->Height);
		windowData->Dispatcher->Dispatch(e);
	}

	void DefaultKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		Event e = Event(EventType::Key);
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

		windowData->Dispatcher->Dispatch(e);
	}

	void DefaultCursorPositionCallback(GLFWwindow *window, double xpos, double ypos)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		Event e = Event(EventType::MouseMove);
		VOLUND_EVENT_MOUSE_MOVE_SET_XPOS(e, xpos);
		VOLUND_EVENT_MOUSE_MOVE_SET_YPOS(e, ypos);

		windowData->Dispatcher->Dispatch(e);
	}

	void DefaultMouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		{
			if (action == GLFW_PRESS)
			{
				Event e = Event(EventType::MouseButton);
				VOLUND_EVENT_MOUSE_BUTTON_SET_BUTTON(e, VOLUND_MOUSE_BUTTON_RIGHT);
				VOLUND_EVENT_MOUSE_BUTTON_SET_ISDOWN(e, true);

				windowData->Dispatcher->Dispatch(e);
			}
			else if (action == GLFW_RELEASE)
			{
				Event e = Event(EventType::MouseButton);
				VOLUND_EVENT_MOUSE_BUTTON_SET_BUTTON(e, VOLUND_MOUSE_BUTTON_RIGHT);
				VOLUND_EVENT_MOUSE_BUTTON_SET_ISDOWN(e, false);

				windowData->Dispatcher->Dispatch(e);
			}
		}
		else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			if (action == GLFW_PRESS)
			{
				Event e = Event(EventType::MouseButton);
				VOLUND_EVENT_MOUSE_BUTTON_SET_BUTTON(e, VOLUND_MOUSE_BUTTON_LEFT);
				VOLUND_EVENT_MOUSE_BUTTON_SET_ISDOWN(e, true);

				windowData->Dispatcher->Dispatch(e);
			}
			else if (action == GLFW_RELEASE)
			{
				Event e = Event(EventType::MouseButton);
				VOLUND_EVENT_MOUSE_BUTTON_SET_BUTTON(e, VOLUND_MOUSE_BUTTON_LEFT);
				VOLUND_EVENT_MOUSE_BUTTON_SET_ISDOWN(e, false);

				windowData->Dispatcher->Dispatch(e);
			}
		}
		else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
		{
			if (action == GLFW_PRESS)
			{
				Event e = Event(EventType::MouseButton);
				VOLUND_EVENT_MOUSE_BUTTON_SET_BUTTON(e, VOLUND_MOUSE_BUTTON_MIDDLE);
				VOLUND_EVENT_MOUSE_BUTTON_SET_ISDOWN(e, true);

				windowData->Dispatcher->Dispatch(e);
			}
			else if (action == GLFW_RELEASE)
			{
				Event e = Event(EventType::MouseButton);
				VOLUND_EVENT_MOUSE_BUTTON_SET_BUTTON(e, VOLUND_MOUSE_BUTTON_MIDDLE);
				VOLUND_EVENT_MOUSE_BUTTON_SET_ISDOWN(e, false);

				windowData->Dispatcher->Dispatch(e);
			}
		}
	}

	void DefaultScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		Event e = Event(EventType::MouseWheel);
		VOLUND_EVENT_MOUSE_WHEEL_SET_DELTA(e, yoffset);

		windowData->Dispatcher->Dispatch(e);
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
		return this->m_WindowData->GlfwWindow;
	}

	void Window::SetCursorMode(const CursorMode newMode)
	{
		this->m_WindowData->CurrentCursorMode = newMode;
		glfwSetInputMode(this->m_WindowData->GlfwWindow, GLFW_CURSOR, (int32_t)newMode);
	}

	CursorMode Window::GetCursorMode()
	{
		return this->m_WindowData->CurrentCursorMode;
	}

	void Window::SetTitle(const std::string &title)
	{
		glfwSetWindowTitle(this->m_WindowData->GlfwWindow, title.c_str());
	}

	void Window::SetVsync(const bool enabled)
	{
		glfwSwapInterval(enabled);
	}

	Vec2 Window::GetSize()
	{
		return Vec2(this->m_WindowData->Width, this->m_WindowData->Height);
	}

	float Window::GetAspectRatio()
	{
		if (this->m_WindowData->Width == 0 || this->m_WindowData->Height == 0)
		{
			return 0;
		}
		else
		{
			return (float)this->m_WindowData->Width / (float)this->m_WindowData->Height;
		}
	}

	void Window::Flush()
	{
		VOLUND_PROFILE_FUNCTION();

		glfwSwapBuffers(this->m_WindowData->GlfwWindow);
	}

	void Window::Reset()
	{
		this->SetCursorMode(CursorMode::Normal);
		this->SetVsync(true);
	}

    void Window::ConnectWindowFocusCallback(GLFWwindowfocusfun callback)
    {
		this->m_WindowData->WindowFocusCallbacks.push_back(callback);
    }

    void Window::ConnectCursorEnterCallback(GLFWcursorenterfun callback)
    {
		this->m_WindowData->CursorEnterCallbacks.push_back(callback);
    }

    void Window::ConnectWindowCloseCallback(GLFWwindowclosefun callback)
    {
		this->m_WindowData->WindowCloseCallbacks.push_back(callback);
    }

    void Window::ConnectWindowSizeCallback(GLFWwindowsizefun callback)
    {
		this->m_WindowData->WindowSizeCallbacks.push_back(callback);
    }

    void Window::ConnectKeyCallback(GLFWkeyfun callback)
    {
		this->m_WindowData->KeyCallbacks.push_back(callback);
    }

    void Window::ConnectCursorPositionCallback(GLFWcursorposfun callback)
    {
		this->m_WindowData->CursorPositionCallbacks.push_back(callback);
    }

    void Window::ConnectMouseButtonCallback(GLFWmousebuttonfun callback)
    {
		this->m_WindowData->MouseButtonCallbacks.push_back(callback);
    }

    void Window::ConnectScrollCallback(GLFWscrollfun callback)
    {
		this->m_WindowData->ScrollCallbacks.push_back(callback);
    }

    void Window::ConnectCharCallback(GLFWcharfun callback)
    {
		this->m_WindowData->CharCallbacks.push_back(callback);
    }

    Window::Window(Ref<EventDispatcher> Dispatcher, uint64_t Width, uint64_t Height, bool FullScreen)
	{
		VOLUND_INFO("Creating window...");

		this->m_WindowData = std::make_shared<WindowData>();
		this->m_WindowData->Dispatcher = Dispatcher;
		
		if (!glfwInit())
		{
		}

		if (FullScreen)
		{
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();

			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

			GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "Volund", monitor, NULL);
			m_WindowData->Height = mode->height;
			m_WindowData->Width = mode->width;
		}
		else
		{
			this->m_WindowData->GlfwWindow = glfwCreateWindow(Width, Height, "Volund", NULL, NULL);

			m_WindowData->Height = Height;
			m_WindowData->Width = Width;
		}

		if (!this->m_WindowData->GlfwWindow)
		{
			glfwTerminate();
			return;
		}
		
		glfwMakeContextCurrent(this->m_WindowData->GlfwWindow);

		glfwSetWindowUserPointer(this->m_WindowData->GlfwWindow, this->m_WindowData.get());

		glfwSetWindowFocusCallback(this->m_WindowData->GlfwWindow, WindowFocusDispatcher);
		glfwSetCursorEnterCallback(this->m_WindowData->GlfwWindow, CursorEnterDispatcher);
		glfwSetWindowCloseCallback(this->m_WindowData->GlfwWindow, WindowCloseDispatcher);
		glfwSetWindowSizeCallback(this->m_WindowData->GlfwWindow, WindowSizeDispatcher);
		glfwSetKeyCallback(this->m_WindowData->GlfwWindow, KeyDispatcher);
		glfwSetCursorPosCallback(this->m_WindowData->GlfwWindow, CursorPositionDispatcher);
		glfwSetMouseButtonCallback(this->m_WindowData->GlfwWindow, MouseButtonDispatcher);
		glfwSetScrollCallback(this->m_WindowData->GlfwWindow, ScrollDispatcher);
		glfwSetCharCallback(this->m_WindowData->GlfwWindow, CharDispatcher);

		this->ConnectWindowCloseCallback(DefaultWindowCloseCallback);
		this->ConnectWindowSizeCallback(DefaultWindowSizeCallback);
		this->ConnectKeyCallback(DefaultKeyCallback);
		this->ConnectCursorPositionCallback(DefaultCursorPositionCallback);
		this->ConnectMouseButtonCallback(DefaultMouseButtonCallback);
		this->ConnectScrollCallback(DefaultScrollCallback);

		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	}

	Window::~Window()
	{
		glfwDestroyWindow(this->m_WindowData->GlfwWindow);
		glfwTerminate();
	}

} // namespace Volund
