#include "PCH/PCH.h"
#include "Window.h"

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WindowsX.h>

namespace Volund
{
	LRESULT CALLBACK WindowProcedure(HWND hwnd, uint32_t msg, WPARAM wparam, LPARAM lparam)
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
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void Window::Update()
	{
		VOLUND_PROFILE_FUNCTION();

		MSG message;

		while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

	void Window::SetProcedureCatch(const ProcCatch procedureCatch)
	{
		this->m_Data.ProcedureCatch = procedureCatch;
	}

	void Window::SetCursorMode(const CursorMode newMode)
	{
		switch (newMode)
		{
		case CursorMode::Normal:
		{
			this->m_Data.CaptureMouse = false;
			this->m_Data.ShowMouse = true;
		}
		break;
		case CursorMode::Hidden:
		{
			this->m_Data.CaptureMouse = false;
			this->m_Data.ShowMouse = false;
		}
		break;
		case CursorMode::Disabled:
		{
			this->m_Data.CaptureMouse = true;
			this->m_Data.ShowMouse = false;
		}
		break;
		case CursorMode::Captured:
		{
			this->m_Data.CaptureMouse = true;
			this->m_Data.ShowMouse = true;
		}
		break;
		}			
		
		if (!this->m_Data.ShowMouse)
		{
			while (ShowCursor(false) >= -1) {}
		}
		else
		{
			while (ShowCursor(true) < 0) {}
		}
	}

	void Window::SetFocus()
	{
		::SetFocus((HWND)this->m_Data.Handle);
		SendMessage((HWND)this->m_Data.Handle, WM_SETFOCUS, 0, 0);
	}

	void Window::SetTitle(const std::string_view title)
	{
		SetWindowText((HWND)this->m_Data.Handle, Utils::ConvertToWString(title).c_str());
	}

	void Window::SetVsync(const bool enabled)
	{
		this->m_Data.Context->SetVSync(enabled);
	}

	Vec2 Window::GetSize()
	{
		return Vec2(this->m_Data.Width, this->m_Data.Height);
	}

	float Window::GetAspectRatio()
	{
		if (this->m_Data.Width == 0 || this->m_Data.Height == 0)
		{
			return 0;
		}
		else
		{
			return (float)this->m_Data.Width / (float)this->m_Data.Height;
		}
	}

	void* Window::GetInstance()
	{
		return this->m_Data.Instance;
	}

	void* Window::GetHandle()
	{
		return this->m_Data.Handle;
	}

	void* Window::GetDeviceContext()
	{
		return this->m_Data.DeviceContext;
	}

	void Window::Show()
	{	
		ShowWindow((HWND)this->m_Data.Handle, SW_SHOW);
		this->Update();
	}

	void Window::Flush()
	{
		VOLUND_PROFILE_FUNCTION();

		::SwapBuffers((HDC)this->m_Data.DeviceContext);
	}

	void Window::Reset()
	{
		this->SetCursorMode(CursorMode::Normal);
		this->SetVsync(true);
	}

	Window::Window(Ref<EventDispatcher> Dispatcher, uint64_t Width, uint64_t Height, bool FullScreen)
	{
		VOLUND_INFO("Creating window...");
		
		this->m_Data.Dispatcher = Dispatcher;
		this->m_Data.FullScreen = FullScreen;

		this->m_Data.Instance = GetModuleHandle(nullptr);

		DWORD dwExStyle;
		DWORD dwStyle;

		if (FullScreen)
		{
			this->m_Data.Width = (uint64_t)GetSystemMetrics(SM_CXSCREEN);
			this->m_Data.Height = (uint64_t)GetSystemMetrics(SM_CYSCREEN);

			DEVMODE ScreenSettings;
			memset(&ScreenSettings, 0, sizeof(ScreenSettings));
			ScreenSettings.dmSize = sizeof(ScreenSettings);
			ScreenSettings.dmPelsWidth = (DWORD)Width;
			ScreenSettings.dmPelsHeight = (DWORD)Height;
			ScreenSettings.dmBitsPerPel = 16;
			ScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			ChangeDisplaySettings(&ScreenSettings, CDS_FULLSCREEN);

			dwExStyle = WS_EX_APPWINDOW;
			dwStyle = WS_POPUP;
		}
		else
		{
			this->m_Data.Width = Width;
			this->m_Data.Height = Height;

			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			dwStyle = WS_OVERLAPPEDWINDOW;
		}

		WNDCLASS Temp;

		if (GetClassInfo((HINSTANCE)this->m_Data.Instance, L"VolundWindow", &Temp) == 0)
		{
			WNDCLASS WindowClass = {};
			WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			WindowClass.lpfnWndProc = (WNDPROC)WindowProcedure;
			WindowClass.cbClsExtra = 0;
			WindowClass.cbWndExtra = 0;
			WindowClass.hInstance = (HINSTANCE)this->m_Data.Instance;
			WindowClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
			WindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
			WindowClass.hbrBackground = nullptr;
			WindowClass.lpszMenuName = nullptr;
			WindowClass.lpszClassName = L"VolundWindow";

			VOLUND_ASSERT(RegisterClass(&WindowClass), "Failed to register Window class!");
		}

		RECT WindowRect = { 0, 0, (LONG)this->m_Data.Width, (LONG)this->m_Data.Height };
		AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);

		this->m_Data.Handle = CreateWindowEx(dwExStyle, L"VolundWindow", L"", WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle, 0,
			0, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top,
			nullptr, nullptr, (HINSTANCE)this->m_Data.Instance, nullptr);

		VOLUND_ASSERT(this->m_Data.Handle, "Failed to create Window!");

		PIXELFORMATDESCRIPTOR PFD =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			16,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			16,
			0,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		this->m_Data.DeviceContext = GetDC((HWND)this->m_Data.Handle);

		VOLUND_ASSERT(this->m_Data.DeviceContext, "Failed to create a Window Device Context!");

		int32_t PixelFormat = ChoosePixelFormat((HDC)this->m_Data.DeviceContext, &PFD);

		VOLUND_ASSERT(PixelFormat, "Unable to find a suitable Pixel Format!");

		VOLUND_ASSERT(SetPixelFormat((HDC)this->m_Data.DeviceContext, PixelFormat, &PFD), "Unable to set Pixel Format!");

		SetWindowLongPtr((HWND)this->m_Data.Handle, GWLP_USERDATA, (LONG_PTR)&this->m_Data);

		this->m_Data.Context = VL::RenderingContext::Create(Window::GetDeviceContext());
		this->m_Data.Context->MakeCurrent();

		this->Reset();
	}

	Window::~Window()
	{
		if (this->m_Data.FullScreen)
		{
			ChangeDisplaySettings(nullptr, 0);
		}

		ShowCursor(true);

		ReleaseDC((HWND)this->m_Data.Handle, (HDC)this->m_Data.DeviceContext);

		DestroyWindow((HWND)this->m_Data.Handle);

		UnregisterClass(L"VolundWindow", (HINSTANCE)this->m_Data.Instance);
	}

} //namespace Volund
