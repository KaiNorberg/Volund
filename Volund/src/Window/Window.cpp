#pragma once

#include "PCH/PCH.h"
#include "Window.h"

#include <Windows.h>
#include <WindowsX.h>
#include <locale>
#include <codecvt>

namespace Volund
{	
	LRESULT CALLBACK WindowProcedure(HWND hwnd, uint32_t msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
		case WM_CREATE:
		{

		}
		break;
		case WM_KEYDOWN:
		{
			WindowData* Data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

			if (Data == nullptr)
			{
				break;
			}

			Data->Dispatcher->Dispatch(KeyEvent((int32_t)wparam, true));
		}
		break;
		case WM_KEYUP:
		{
			WindowData* Data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

			if (Data == nullptr)
			{
				break;
			}

			Data->Dispatcher->Dispatch(KeyEvent((int32_t)wparam, false));
		}
		break;
		case WM_MOUSEMOVE:
		{
			WindowData* Data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

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

				RECT WindowRect = {};
				GetClientRect(hwnd, &WindowRect);

				int32_t MiddleX = WindowRect.left + (WindowRect.right - WindowRect.left) / 2;
				int32_t MiddleY = WindowRect.top + (WindowRect.bottom - WindowRect.top) / 2;

				POINT WindowCenter = { MiddleX, MiddleY };
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
			WindowData* Data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

			if (Data == nullptr)
			{
				break;
			}

			Data->Dispatcher->Dispatch(MouseButtonEvent(VOLUND_MOUSE_BUTTON_LEFT, true));
		}
		break;
		case WM_LBUTTONUP:
		{
			WindowData* Data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

			if (Data == nullptr)
			{
				break;
			}

			Data->Dispatcher->Dispatch(MouseButtonEvent(VOLUND_MOUSE_BUTTON_LEFT, false));
		}
		break;
		case WM_MBUTTONDOWN:
		{
			WindowData* Data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

			if (Data == nullptr)
			{
				break;
			}

			Data->Dispatcher->Dispatch(MouseButtonEvent(VOLUND_MOUSE_BUTTON_MIDDLE, true));
		}
		break;
		case WM_MBUTTONUP:
		{
			WindowData* Data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

			if (Data == nullptr)
			{
				break;
			}

			Data->Dispatcher->Dispatch(MouseButtonEvent(VOLUND_MOUSE_BUTTON_MIDDLE, false));
		}
		break;
		case WM_RBUTTONDOWN:
		{
			WindowData* Data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

			if (Data == nullptr)
			{
				break;
			}

			Data->Dispatcher->Dispatch(MouseButtonEvent(VOLUND_MOUSE_BUTTON_RIGHT, true));
		}
		break;
		case WM_RBUTTONUP:
		{
			WindowData* Data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

			if (Data == nullptr)
			{
				break;
			}

			Data->Dispatcher->Dispatch(MouseButtonEvent(VOLUND_MOUSE_BUTTON_RIGHT, false));
		}
		break;
		case WM_MOUSEWHEEL:
		{
			WindowData* Data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

			if (Data == nullptr)
			{
				break;
			}

			uint32_t zDelta = GET_WHEEL_DELTA_WPARAM(wparam);

			Data->Dispatcher->Dispatch(ScrollEvent(0, zDelta));
		}
		break;
		case WM_SIZE:
		{
			WindowData* Data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

			if (Data == nullptr)
			{
				break;
			}

			RECT WindowRect = {};
			GetClientRect(hwnd, &WindowRect);

			Data->Width = WindowRect.right;
			Data->Height = WindowRect.bottom;

			Data->Dispatcher->Dispatch(WindowSizeEvent((uint32_t)Data->Width, (uint32_t)Data->Height));
		}
		break;
		case WM_SETFOCUS:
		{

		}
		break;
		case WM_KILLFOCUS:
		{

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

	void Window::SwapBuffers()
	{
		::SwapBuffers((HDC)this->_DeviceContext);
	}

	void Window::Update()
	{
		MSG Message;

		while (PeekMessageW(&Message, nullptr, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}

	void Window::SetCursorMode(std::string const& NewMode)
	{
		if (NewMode == "Normal")
		{
			ShowCursor(true);
			this->_Data.CaptureMouse = false;
		}
		else if (NewMode == "Hidden")
		{
			ShowCursor(false);
			this->_Data.CaptureMouse = false;
		}
		else if (NewMode == "Disabled")
		{
			ShowCursor(false);
			this->_Data.CaptureMouse = true;
		}
		else if (NewMode == "Captured")
		{
			ShowCursor(true);
			this->_Data.CaptureMouse = true;
		}		
		else
		{
			VOLUND_ERROR("Unrecognized Cursor Mode (%s)", NewMode.c_str());
		}
	}

	void Window::SetTitle(std::string const& Title)
	{
		SetWindowText((HWND)this->_Handle, this->ConvertToWString(Title).c_str());
	}

	Vec2 Window::GetSize()
	{
		return Vec2(this->_Data.Width, this->_Data.Height);
	}

	void* Window::GetDeviceContext()
	{
		return this->_DeviceContext;
	}

	std::wstring Window::ConvertToWString(std::string const& String)
	{
		return std::wstring(String.begin(), String.end());
	}

	Window::Window(Ref<EventDispatcher>& Dispatcher, uint64_t Width, uint64_t Height, bool FullScreen)
	{
		VOLUND_INFO("Creating window...");

		this->_Data.Dispatcher = Dispatcher;

		this->_Instance = GetModuleHandle(NULL);

		WNDCLASS WindowClass = {};
		WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;   
		WindowClass.lpfnWndProc = (WNDPROC)WindowProcedure;    
		WindowClass.cbClsExtra = 0;               
		WindowClass.cbWndExtra = 0;               
		WindowClass.hInstance = (HINSTANCE)this->_Instance;
		WindowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);    
		WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);      
		WindowClass.hbrBackground = NULL;                    
		WindowClass.lpszMenuName = NULL;                
		WindowClass.lpszClassName = L"VolundWindow";                 

		VOLUND_ASSERT(RegisterClass(&WindowClass), "Failed to register Window class!");

		DWORD dwExStyle;
		DWORD dwStyle;

		if (FullScreen)
		{
			this->_Data.Width = GetSystemMetrics(SM_CXSCREEN);
			this->_Data.Height = GetSystemMetrics(SM_CYSCREEN);

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
			this->_Data.Width = Width;
			this->_Data.Height = Height;

			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			dwStyle = WS_OVERLAPPEDWINDOW;
		}

		RECT WindowRect = { 0,0, (LONG)this->_Data.Width, (LONG)this->_Data.Height };
		AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);

		this->_Handle = CreateWindowEx(dwExStyle, L"VolundWindow", L"", WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle, 0, 0, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top,
			NULL, NULL, (HINSTANCE)this->_Instance, NULL);

		VOLUND_ASSERT(this->_Handle, "Failed to register Window class!");

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

		this->_DeviceContext = GetDC((HWND)this->_Handle);

		VOLUND_ASSERT(this->_DeviceContext, "Failed to create a Window Device Context!");

		uint32_t PixelFormat = ChoosePixelFormat((HDC)this->_DeviceContext, &PFD);

		VOLUND_ASSERT(PixelFormat, "Unable to find a suitable Pixel Format!");

		VOLUND_ASSERT(SetPixelFormat((HDC)this->_DeviceContext, PixelFormat, &PFD), "Unable to set Pixel Format!");

		SetWindowLongPtr((HWND)this->_Handle, GWLP_USERDATA, (LONG_PTR)&this->_Data);

		ShowWindow((HWND)this->_Handle, SW_SHOW);
		UpdateWindow((HWND)this->_Handle);
	}

	Window::~Window()
	{
		DestroyWindow((HWND)this->_Handle);
	}

} //namespace Volund