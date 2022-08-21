#pragma once

#include "PCH/PCH.h"
#include "Window.h"

#define GLFW_ERROR_CHECK()\
{\
	const char* Description;\
	int Code = glfwGetError(&Description);\
	if(Description)\
	{\
		Console::LogError(Description);\
	}\
}\

namespace Volund
{
	static bool GLFWInitialized = false;
	
	void WindowCloseCallback(GLFWwindow* WindowObject)
	{
		WindowData* Data = (WindowData*)glfwGetWindowUserPointer(WindowObject);

		Data->Dispatcher->PushEvent(new WindowCloseEvent());
	}

	void WindowSizeCallback(GLFWwindow* WindowObject, int32_t Width, int32_t Height)
	{
		WindowData* Data = (WindowData*)glfwGetWindowUserPointer(WindowObject);
		
		if (Data->Width != Width || Data->Height != Height)
		{
			Data->Width = Width;
			Data->Height = Height;

			Data->Dispatcher->PushEvent(new WindowSizeEvent(Width, Height));
		}
	}

	void KeyCallback(GLFWwindow* WindowObject, int32_t Key, int32_t Scancode, int32_t Action, int32_t Mods)
	{
		WindowData* Data = (WindowData*)glfwGetWindowUserPointer(WindowObject);

		Data->Dispatcher->PushEvent(new KeyEvent(Key, Scancode, Action, Mods));
	}

	void MouseButtonCallback(GLFWwindow* WindowObject, int32_t Button, int32_t Action, int32_t Mods)
	{
		WindowData* Data = (WindowData*)glfwGetWindowUserPointer(WindowObject);

		Data->Dispatcher->PushEvent(new MouseButtonEvent(Button, Action, Mods));
	}

	void ScrollCallback(GLFWwindow* WindowObject, double xOffset, double yOffset)
	{
		WindowData* Data = (WindowData*)glfwGetWindowUserPointer(WindowObject);

		Data->Dispatcher->PushEvent(new ScrollEvent(xOffset, yOffset));
	}

	void CursorPosCallback(GLFWwindow* WindowObject, double xPos, double yPos)
	{
		WindowData* Data = (WindowData*)glfwGetWindowUserPointer(WindowObject);

		Data->Dispatcher->PushEvent(new CursorPosEvent(xPos, yPos));
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void Window::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(this->_WindowObject);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(this->_WindowObject);
	}

	void Window::MakeFullscreen()
	{
		int32_t Count;
		GLFWmonitor** Monitors = glfwGetMonitors(&Count);

		JSON ConfigFile = LoadJSON(CONFIG_JSON);

		int32_t SelectedMonitor = ConfigFile["Window"]["Monitor"];
		if (SelectedMonitor >= Count)
		{
			SelectedMonitor = 0;
		}

		const GLFWvidmode* Mode = glfwGetVideoMode(Monitors[SelectedMonitor]);

		this->_Data.Width = Mode->width;
		this->_Data.Height = Mode->height;

		glfwWindowHint(GLFW_RED_BITS, Mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, Mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, Mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, Mode->refreshRate); 
		
		glfwSetWindowMonitor(this->_WindowObject, Monitors[SelectedMonitor], 0, 0, Mode->width, Mode->height, Mode->refreshRate);
	}

	void Window::SetVSync(bool Enabled)
	{
		glfwSwapInterval(Enabled);
	}

	Window::Window(EventDispatcher* Dispatcher)
	{
		Console::Log("Creating window...");

		JSON ConfigFile = LoadJSON(CONFIG_JSON);

		this->_Data.Dispatcher = Dispatcher;
		this->_Data.Width = ConfigFile["Window"]["Width"];
		this->_Data.Height = ConfigFile["Window"]["Height"];

		if (!GLFWInitialized)
		{
			glfwInit();
			GLFW_ERROR_CHECK();
			GLFWInitialized = true;
		}

		this->_WindowObject = glfwCreateWindow(this->_Data.Width, this->_Data.Height, ((std::string)ConfigFile["Window"]["Title"]).c_str(), NULL, NULL);
		GLFW_ERROR_CHECK();

		glfwMakeContextCurrent(_WindowObject);
		GLFW_ERROR_CHECK();

		//Read settings

		if (ConfigFile["Window"]["FullScreen"] == true)
		{
			this->MakeFullscreen();
		}
		this->SetVSync(ConfigFile["Window"]["VSync"].get<bool>());

		//Set callbacks
		glfwSetWindowUserPointer(this->_WindowObject, &this->_Data);
		glfwSetWindowCloseCallback(this->_WindowObject, WindowCloseCallback);
		glfwSetWindowSizeCallback(this->_WindowObject, WindowSizeCallback);
		glfwSetKeyCallback(this->_WindowObject, KeyCallback);
		glfwSetMouseButtonCallback(this->_WindowObject, MouseButtonCallback);
		glfwSetScrollCallback(this->_WindowObject, ScrollCallback);
		glfwSetCursorPosCallback(this->_WindowObject, CursorPosCallback);

		GLFW_ERROR_CHECK();
	}

	Window::~Window()
	{
		glfwDestroyWindow(_WindowObject);

		glfwTerminate();
	
		GLFWInitialized = false;
	}

} //namespace Volund