#pragma once

#include "EventDispatcher/EventDispatcher.h"

#include "Rendering/Framebuffer/Framebuffer.h"

#include <GLFW/glfw3.h>

namespace Volund
{
	struct WindowData
	{
		uint64_t Width = 0;
		uint64_t Height = 0;

		GLFWwindow* GlfwWindow;

		bool IsCursorEnabled = true;

		Ref<EventDispatcher> Dispatcher;

		std::vector<GLFWwindowfocusfun> WindowFocusCallbacks;
		std::vector<GLFWcursorenterfun> CursorEnterCallbacks;
		std::vector<GLFWwindowclosefun> WindowCloseCallbacks;
		std::vector<GLFWwindowsizefun> WindowSizeCallbacks;
		std::vector<GLFWkeyfun> KeyCallbacks;
		std::vector<GLFWcursorposfun> CursorPositionCallbacks;
		std::vector<GLFWmousebuttonfun> MouseButtonCallbacks;
		std::vector<GLFWscrollfun> ScrollCallbacks;
		std::vector<GLFWcharfun> CharCallbacks;
	};

	class Window
	{
	public:

		void Update();

		GLFWwindow* GetGlfwWindow();

		void SetCursorEnabled(bool enabled);

		bool IsCursorEnabled();

		void SetTitle(const std::string& title);

		void SetVsync(bool enabled);

		Vec2 GetSize();

		float GetAspectRatio();

		void Flush();

		void SetIcon(const std::string& filepath);

		void ConnectWindowFocusCallback(GLFWwindowfocusfun callback);		
		void ConnectCursorEnterCallback(GLFWcursorenterfun callback);
		void ConnectWindowCloseCallback(GLFWwindowclosefun callback);
		void ConnectWindowSizeCallback(GLFWwindowsizefun callback);
		void ConnectKeyCallback(GLFWkeyfun callback);
		void ConnectCursorPositionCallback(GLFWcursorposfun callback);
		void ConnectMouseButtonCallback(GLFWmousebuttonfun callback);
		void ConnectScrollCallback(GLFWscrollfun callback);
		void ConnectCharCallback(GLFWcharfun callback);

		Window(Ref<EventDispatcher> dispatcher, uint64_t width, uint64_t height, bool fullScreen);

		~Window();

	private:

		Ref<WindowData> m_WindowData;
	};
}
