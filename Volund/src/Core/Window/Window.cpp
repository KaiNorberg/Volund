#include "PCH/PCH.h"
#include "Window.h"

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WindowsX.h>

namespace Volund
{
	LRESULT CALLBACK WindowProcedure(HWND hwnd, uint32_t msg, WPARAM wparam, LPARAM lparam)
	{
		WindowData* Data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

		if (Data != nullptr && Data->ProcedureCatch != nullptr)
		{
			if (Data->ProcedureCatch(hwnd, msg, wparam, lparam))
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
			if (Data == nullptr)
			{
				break;
			}

			Data->Dispatcher->Dispatch(KeyEvent((uint32_t)wparam, true));
		}
		break;
		case WM_KEYUP:
		{
			if (Data == nullptr)
			{
				break;
			}

			Data->Dispatcher->Dispatch(KeyEvent((uint32_t)wparam, false));
		}
		break;
		case WM_MOUSEMOVE:
		{
			if (Data == nullptr || GetFocus() != hwnd)
			{
				break;
			}

			int32_t xPos = GET_X_LPARAM(lparam);
			int32_t yPos = GET_Y_LPARAM(lparam);

			if (Data->CaptureMouse)
			{
				static int32_t VirtualXPos = 0;
				static int32_t VirtualYPos = 0;

				RECT ScreenSpaceRect;
				GetWindowRect(hwnd, &ScreenSpaceRect);
				ClipCursor(&ScreenSpaceRect);

				RECT WindowRect = {};
				GetClientRect(hwnd, &WindowRect);

				int32_t MiddleX = WindowRect.left + (WindowRect.right - WindowRect.left) / 2;
				int32_t MiddleY = WindowRect.top + (WindowRect.bottom - WindowRect.top) / 2;

				POINT WindowCenter = {MiddleX, MiddleY};
				ClientToScreen(hwnd, &WindowCenter);
				SetCursorPos(WindowCenter.x, WindowCenter.y);

				VirtualXPos += xPos - MiddleX;
				VirtualYPos += yPos - MiddleY;

				Data->Dispatcher->Dispatch(MouseMoveEvent(VirtualXPos, VirtualYPos));
			}
			else
			{
				Data->Dispatcher->Dispatch(MouseMoveEvent(xPos, yPos));
			}
		}
		break;
		case WM_LBUTTONDOWN:
		{
			if (Data == nullptr)
			{
				break;
			}

			Data->Dispatcher->Dispatch(MouseButtonEvent(VOLUND_MOUSE_BUTTON_LEFT, true));
		}
		break;
		case WM_LBUTTONUP:
		{
			if (Data == nullptr)
			{
				break;
			}

			Data->Dispatcher->Dispatch(MouseButtonEvent(VOLUND_MOUSE_BUTTON_LEFT, false));
		}
		break;
		case WM_MBUTTONDOWN:
		{
			if (Data == nullptr)
			{
				break;
			}

			Data->Dispatcher->Dispatch(MouseButtonEvent(VOLUND_MOUSE_BUTTON_MIDDLE, true));
		}
		break;
		case WM_MBUTTONUP:
		{
			if (Data == nullptr)
			{
				break;
			}

			Data->Dispatcher->Dispatch(MouseButtonEvent(VOLUND_MOUSE_BUTTON_MIDDLE, false));
		}
		break;
		case WM_RBUTTONDOWN:
		{
			if (Data == nullptr)
			{
				break;
			}

			Data->Dispatcher->Dispatch(MouseButtonEvent(VOLUND_MOUSE_BUTTON_RIGHT, true));
		}
		break;
		case WM_RBUTTONUP:
		{
			if (Data == nullptr)
			{
				break;
			}

			Data->Dispatcher->Dispatch(MouseButtonEvent(VOLUND_MOUSE_BUTTON_RIGHT, false));
		}
		break;
		case WM_MOUSEWHEEL:
		{
			if (Data == nullptr)
			{
				break;
			}

			int16_t zDelta = GET_WHEEL_DELTA_WPARAM(wparam);

			Data->Dispatcher->Dispatch(ScrollEvent(0, (uint32_t)zDelta));
		}
		break;
		case WM_SIZE:
		{
			if (Data == nullptr)
			{
				break;
			}

			RECT WindowRect = {};
			GetClientRect(hwnd, &WindowRect);

			Data->Width = (uint64_t)WindowRect.right;
			Data->Height = (uint64_t)WindowRect.bottom;

			Data->Dispatcher->Dispatch(WindowSizeEvent((uint32_t)Data->Width, (uint32_t)Data->Height));
		}
		break;
		case WM_SETFOCUS:
		{
			if (!Data->ShowMouse)
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
			WindowData* Data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

			if (Data == nullptr)
			{
				break;
			}

			Data->Dispatcher->Dispatch(WindowCloseEvent());
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
		MSG Message;

		while (PeekMessageW(&Message, nullptr, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}

	void Window::SetProcedureCatch(ProcCatch ProcedureCatch)
	{
		_Data.ProcedureCatch = ProcedureCatch;
	}

	void Window::SetCursorMode(CursorMode NewMode)
	{
		switch (NewMode)
		{
		case CursorMode::NORMAL:
		{
			_Data.CaptureMouse = false;
			_Data.ShowMouse = true;
		}
		break;
		case CursorMode::HIDDEN:
		{
			_Data.CaptureMouse = false;
			_Data.ShowMouse = false;
		}
		break;
		case CursorMode::DISABLED:
		{
			_Data.CaptureMouse = true;
			_Data.ShowMouse = false;
		}
		break;
		case CursorMode::CAPTURED:
		{
			_Data.CaptureMouse = true;
			_Data.ShowMouse = true;
		}
		break;
		}			
		
		if (!_Data.ShowMouse)
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
		::SetFocus((HWND)_Data._Handle);
		SendMessage((HWND)_Data._Handle, WM_SETFOCUS, 0, 0);
	}

	void Window::SetTitle(std::string_view Title)
	{
		SetWindowText((HWND)_Data._Handle, Utils::ConvertToWString(Title).c_str());
	}

	void Window::SetVsync(bool Enabled)
	{
		_Data.Context->SetVSync(Enabled);
	}

	Vec2 Window::GetSize()
	{
		return Vec2(_Data.Width, _Data.Height);
	}

	float Window::GetAspectRatio()
	{
		if (_Data.Width == 0 || _Data.Height == 0)
		{
			return 0;
		}
		else
		{
			return (float)_Data.Width / (float)_Data.Height;
		}
	}

	void* Window::GetInstance()
	{
		return _Data._Instance;
	}

	void* Window::GetHandle()
	{
		return _Data._Handle;
	}

	void* Window::GetDeviceContext()
	{
		return _Data._DeviceContext;
	}

	void Window::Show()
	{		
		ShowWindow((HWND)_Data._Handle, SW_SHOW);
		Window::Update();
	}

	void Window::Flush()
	{
		_Data.Context->Flush();
		::SwapBuffers((HDC)_Data._DeviceContext);
	}

	void Window::Reset()
	{
		Window::SetCursorMode(CursorMode::NORMAL);
		Window::SetVsync(true);
	}

	void Window::Create(Ref<EventDispatcher> Dispatcher, uint64_t Width, uint64_t Height, bool FullScreen)
	{
		static Window _Singleton;

		if (_Data._Handle != nullptr)
		{
			Window::Destroy();
		}

		VOLUND_INFO("Creating window...");

		_Data.Dispatcher = Dispatcher;
		_Data.FullScreen = FullScreen;

		_Data._Instance = GetModuleHandle(nullptr);

		DWORD dwExStyle;
		DWORD dwStyle;

		if (FullScreen)
		{
			_Data.Width = (uint64_t)GetSystemMetrics(SM_CXSCREEN);
			_Data.Height = (uint64_t)GetSystemMetrics(SM_CYSCREEN);

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
			_Data.Width = Width;
			_Data.Height = Height;

			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			dwStyle = WS_OVERLAPPEDWINDOW;
		}

		WNDCLASS Temp;

		if (GetClassInfo((HINSTANCE)_Data._Instance, L"VolundWindow", &Temp) == 0)
		{
			WNDCLASS WindowClass = {};
			WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			WindowClass.lpfnWndProc = (WNDPROC)WindowProcedure;
			WindowClass.cbClsExtra = 0;
			WindowClass.cbWndExtra = 0;
			WindowClass.hInstance = (HINSTANCE)_Data._Instance;
			WindowClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
			WindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
			WindowClass.hbrBackground = nullptr;
			WindowClass.lpszMenuName = nullptr;
			WindowClass.lpszClassName = L"VolundWindow";

			VOLUND_ASSERT(RegisterClass(&WindowClass), "Failed to register Window class!");
		}

		RECT WindowRect = { 0, 0, (LONG)_Data.Width, (LONG)_Data.Height };
		AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);

		_Data._Handle = CreateWindowEx(dwExStyle, L"VolundWindow", L"", WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle, 0,
			0, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top,
			nullptr, nullptr, (HINSTANCE)_Data._Instance, nullptr);

		VOLUND_ASSERT(_Data._Handle, "Failed to create Window!");

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

		_Data._DeviceContext = GetDC((HWND)_Data._Handle);

		VOLUND_ASSERT(_Data._DeviceContext, "Failed to create a Window Device Context!");

		int32_t PixelFormat = ChoosePixelFormat((HDC)_Data._DeviceContext, &PFD);

		VOLUND_ASSERT(PixelFormat, "Unable to find a suitable Pixel Format!");

		VOLUND_ASSERT(SetPixelFormat((HDC)_Data._DeviceContext, PixelFormat, &PFD), "Unable to set Pixel Format!");

		SetWindowLongPtr((HWND)_Data._Handle, GWLP_USERDATA, (LONG_PTR)&_Data);

		_Data.Context = VL::Context::Create(Window::GetDeviceContext());
		_Data.Context->MakeCurrent();

		Window::Reset();
	}

	void Window::Destroy()
	{
		if (_Data.FullScreen)
		{
			ChangeDisplaySettings(nullptr, 0);
		}

		ShowCursor(true);

		ReleaseDC((HWND)_Data._Handle, (HDC)_Data._DeviceContext);

		DestroyWindow((HWND)_Data._Handle);

		UnregisterClass(L"VolundWindow", (HINSTANCE)_Data._Instance);
	}

	Window::~Window()
	{
		this->Destroy();
	}

} //namespace Volund
