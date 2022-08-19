#pragma once

#include "PCH/PCH.h"
#include "Window.h"

#define GLFW_ERROR_CHECK()\
{\
	const char* Description;\
	int Code = glfwGetError(&Description);\
	if(Description)\
	{\
		Console::LogError("GLFW: ", Description);\
	}\
}\

namespace Volund
{
	void Window::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(this->WindowObject);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(this->WindowObject);
	}

	void Window::MakeFullscreen()
	{
		int32_t Count;
		GLFWmonitor** Monitors = glfwGetMonitors(&Count);

		JSON ConfigFile = JSON::Load(CONFIG_JSON);

		int32_t SelectedMonitor = ConfigFile["Window"]["Monitor"];
		if (SelectedMonitor >= Count)
		{
			SelectedMonitor = 0;
		}

		const GLFWvidmode* Mode = glfwGetVideoMode(Monitors[SelectedMonitor]);

		glfwWindowHint(GLFW_RED_BITS, Mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, Mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, Mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, Mode->refreshRate); 
		
		glfwSetWindowMonitor(this->WindowObject, Monitors[SelectedMonitor], 0, 0, Mode->width, Mode->height, Mode->refreshRate);
	}

	Window::Window()
	{
		Console::Log("Creating window...");

		glfwInit();
		GLFW_ERROR_CHECK();

		JSON ConfigFile = JSON::Load(CONFIG_JSON);

		this->WindowObject = glfwCreateWindow(ConfigFile["Window"]["Width"], ConfigFile["Window"]["Height"], ((std::string)ConfigFile["Window"]["Title"]).c_str(), NULL, NULL);
		GLFW_ERROR_CHECK();

		if (ConfigFile["Window"]["FullScreen"] == true)
		{
			this->MakeFullscreen();
		}

		glfwMakeContextCurrent(WindowObject);
		GLFW_ERROR_CHECK();
	}

	Window::~Window()
	{
		glfwDestroyWindow(WindowObject);

		glfwTerminate();
	}

} //namespace Volund