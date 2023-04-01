#include "PCH/PCH.h"
#include "Window.h"

#include <backends/imgui_impl_glfw.h>

namespace Volund
{
	/*LRESULT CALLBACK WindowProcedure(HWND hwnd, uint32_t msg, WPARAM wparam, LPARAM lparam)
	{
		WindowData* data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

		if (data != nullptr && data->ProcedureCatch != nullptr)
		{
			if (data->ProcedureCatch(hwnd, msg, wparam, lparam))
			{
				return true;
			}
		}

		switch (msg)
		{
		case WM_CREATE:
		{
		}
		break;
		case WM_KEYDOWN:
		{
			if (data == nullptr)
			{
				break;
			}

			Event e = Event(EventType::Key);
			VOLUND_EVENT_KEY_SET_KEY(e, (uint32_t)wparam);
			VOLUND_EVENT_KEY_SET_ISDOWN(e, true);

			data->Dispatcher->Dispatch(e);
		}
		break;
		case WM_KEYUP:
		{
			if (data == nullptr)
			{
				break;
			}

			Event e = Event(EventType::Key);
			VOLUND_EVENT_KEY_SET_KEY(e, (uint32_t)wparam);
			VOLUND_EVENT_KEY_SET_ISDOWN(e, false);

			data->Dispatcher->Dispatch(e);
		}
		break;
		case WM_MOUSEMOVE:
		{
			if (data == nullptr || GetFocus() != hwnd)
			{
				break;
			}

			int32_t xPos = GET_X_LPARAM(lparam);
			int32_t yPos = GET_Y_LPARAM(lparam);

			if (data->CaptureMouse)
			{
				static int32_t virtualXPos = 0;
				static int32_t virtualYPos = 0;

				RECT screenSpaceRect;
				GetWindowRect(hwnd, &screenSpaceRect);
				ClipCursor(&screenSpaceRect);

				RECT windowRect = {};
				GetClientRect(hwnd, &windowRect);

				const int32_t middleX = windowRect.left + (windowRect.right - windowRect.left) / 2;
				const int32_t middleY = windowRect.top + (windowRect.bottom - windowRect.top) / 2;

				POINT windowCenter = {middleX, middleY};
				ClientToScreen(hwnd, &windowCenter);
				SetCursorPos(windowCenter.x, windowCenter.y);

				virtualXPos += xPos - middleX;
				virtualYPos += yPos - middleY;

				Event e = Event(EventType::MouseMove);
				VOLUND_EVENT_MOUSE_MOVE_SET_XPOS(e, virtualXPos);
				VOLUND_EVENT_MOUSE_MOVE_SET_YPOS(e, virtualYPos);

				data->Dispatcher->Dispatch(e);
			}
			else
			{
				Event e = Event(EventType::MouseMove);
				VOLUND_EVENT_MOUSE_MOVE_SET_XPOS(e, xPos);
				VOLUND_EVENT_MOUSE_MOVE_SET_YPOS(e, yPos);

				data->Dispatcher->Dispatch(e);
			}
		}
		break;
		case WM_LBUTTONDOWN:
		{
			if (data == nullptr)
			{
				break;
			}

			Event e = Event(EventType::MouseButton);
			VOLUND_EVENT_MOUSE_BUTTON_SET_BUTTON(e, VOLUND_MOUSE_BUTTON_LEFT);
			VOLUND_EVENT_MOUSE_BUTTON_SET_ISDOWN(e, true);

			data->Dispatcher->Dispatch(e);
		}
		break;
		case WM_LBUTTONUP:
		{
			if (data == nullptr)
			{
				break;
			}

			Event e = Event(EventType::MouseButton);
			VOLUND_EVENT_MOUSE_BUTTON_SET_BUTTON(e, VOLUND_MOUSE_BUTTON_LEFT);
			VOLUND_EVENT_MOUSE_BUTTON_SET_ISDOWN(e, false);

			data->Dispatcher->Dispatch(e);
		}
		break;
		case WM_MBUTTONDOWN:
		{
			if (data == nullptr)
			{
				break;
			}

			Event e = Event(EventType::MouseButton);
			VOLUND_EVENT_MOUSE_BUTTON_SET_BUTTON(e, VOLUND_MOUSE_BUTTON_MIDDLE);
			VOLUND_EVENT_MOUSE_BUTTON_SET_ISDOWN(e, true);

			data->Dispatcher->Dispatch(e);
		}
		break;
		case WM_MBUTTONUP:
		{
			if (data == nullptr)
			{
				break;
			}

			Event e = Event(EventType::MouseButton);
			VOLUND_EVENT_MOUSE_BUTTON_SET_BUTTON(e, VOLUND_MOUSE_BUTTON_MIDDLE);
			VOLUND_EVENT_MOUSE_BUTTON_SET_ISDOWN(e, false);

			data->Dispatcher->Dispatch(e);
		}
		break;
		case WM_RBUTTONDOWN:
		{
			if (data == nullptr)
			{
				break;
			}

			Event e = Event(EventType::MouseButton);
			VOLUND_EVENT_MOUSE_BUTTON_SET_BUTTON(e, VOLUND_MOUSE_BUTTON_RIGHT);
			VOLUND_EVENT_MOUSE_BUTTON_SET_ISDOWN(e, true);

			data->Dispatcher->Dispatch(e);
		}
		break;
		case WM_RBUTTONUP:
		{
			if (data == nullptr)
			{
				break;
			}

			Event e = Event(EventType::MouseButton);
			VOLUND_EVENT_MOUSE_BUTTON_SET_BUTTON(e, VOLUND_MOUSE_BUTTON_RIGHT);
			VOLUND_EVENT_MOUSE_BUTTON_SET_ISDOWN(e, false);

			data->Dispatcher->Dispatch(e);
		}
		break;
		case WM_MOUSEWHEEL:
		{
			if (data == nullptr)
			{
				break;
			}

			int16_t zDelta = GET_WHEEL_DELTA_WPARAM(wparam);

			Event e = Event(EventType::MouseWheel);
			VOLUND_EVENT_MOUSE_WHEEL_SET_DELTA(e, zDelta);

			data->Dispatcher->Dispatch(e);
		}
		break;
		case WM_SIZE:
		{
			if (data == nullptr)
			{
				break;
			}

			RECT windowRect = {};
			GetClientRect(hwnd, &windowRect);

			data->Width = (uint64_t)windowRect.right;
			data->Height = (uint64_t)windowRect.bottom;

			Event e = Event(EventType::WindowSize);
			VOLUND_EVENT_WINDOW_SIZE_SET_WIDTH(e, data->Width);
			VOLUND_EVENT_WINDOW_SIZE_SET_HEIGHT(e, data->Height);

			data->Dispatcher->Dispatch(e);
		}
		break;
		case WM_SETFOCUS:
		{
			if (!data->ShowMouse)
			{
				while (ShowCursor(false) >= -1) {}
			}
		}
		break;
		case WM_KILLFOCUS:
		{
			ClipCursor(nullptr);

			while (ShowCursor(true) < 0) {}
		}
		break;
		case WM_MOVE:
		{
		}
		break;
		case WM_CLOSE:
		{
			if (data == nullptr)
			{
				break;
			}
				Event e = Event(EventType::WindowClose);
			data->Dispatcher->Dispatch(e);
		}
		break;
		case WM_DESTROY:
		{
		}
		break;
		default:
			return DefWindowProc(hwnd, msg, wparam, lparam);
		}

		return NULL;
	}*/

	Ref<WindowData> windowData;

	void FocusCallback(GLFWwindow* window, int focused)
	{
		ImGui_ImplGlfw_WindowFocusCallback(window, focused);
	}

	void CursorEnterCallback(GLFWwindow* window, int entered)
	{
		ImGui_ImplGlfw_CursorEnterCallback(window, entered);
	}

	void CloseCallback(GLFWwindow *window)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		Event e = Event(EventType::WindowClose);
		windowData->Dispatcher->Dispatch(e);
	}

	void WindowSizeCallback(GLFWwindow *window, int width, int height)
	{
		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		Event e = Event(EventType::WindowSize);
		VOLUND_EVENT_WINDOW_SIZE_SET_WIDTH(e, windowData->Width);
		VOLUND_EVENT_WINDOW_SIZE_SET_HEIGHT(e, windowData->Height);
		windowData->Dispatcher->Dispatch(e);
	}

	void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);

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

	void CursorPositionCallback(GLFWwindow *window, double xpos, double ypos)
	{
		ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);

		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		Event e = Event(EventType::MouseMove);
		VOLUND_EVENT_MOUSE_MOVE_SET_XPOS(e, xpos);
		VOLUND_EVENT_MOUSE_MOVE_SET_YPOS(e, ypos);

		windowData->Dispatcher->Dispatch(e);
	}

	void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
	{
		ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

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

	void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
	{
		ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);

		WindowData *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

		Event e = Event(EventType::MouseWheel);
		VOLUND_EVENT_MOUSE_WHEEL_SET_DELTA(e, yoffset);

		windowData->Dispatcher->Dispatch(e);
	}

	void CharCallback(GLFWwindow *window, unsigned int c)
	{
		ImGui_ImplGlfw_CharCallback(window, c);
	}

	void MonitorCallback(GLFWmonitor* monitor, int event)
	{
		ImGui_ImplGlfw_MonitorCallback(monitor, event);
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

	Window::Window(Ref<EventDispatcher> Dispatcher, uint64_t Width, uint64_t Height, bool FullScreen)
	{
		VOLUND_INFO("Creating window...");

		this->m_WindowData = std::make_shared<WindowData>();

		windowData = this->m_WindowData;
		windowData->Dispatcher = Dispatcher;

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

		glfwSetWindowFocusCallback(this->m_WindowData->GlfwWindow, FocusCallback);
		glfwSetCursorEnterCallback(this->m_WindowData->GlfwWindow, CursorEnterCallback);
		glfwSetWindowCloseCallback(this->m_WindowData->GlfwWindow, CloseCallback);
		glfwSetWindowSizeCallback(this->m_WindowData->GlfwWindow, WindowSizeCallback);
		glfwSetKeyCallback(this->m_WindowData->GlfwWindow, KeyCallback);
		glfwSetCursorPosCallback(this->m_WindowData->GlfwWindow, CursorPositionCallback);
		glfwSetMouseButtonCallback(this->m_WindowData->GlfwWindow, MouseButtonCallback);
		glfwSetScrollCallback(this->m_WindowData->GlfwWindow, ScrollCallback);
		glfwSetCharCallback(this->m_WindowData->GlfwWindow, CharCallback);
		glfwSetMonitorCallback(MonitorCallback);

		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	}

	Window::~Window()
	{
		glfwDestroyWindow(this->m_WindowData->GlfwWindow);
		glfwTerminate();
	}

} // namespace Volund
