#pragma once

#include "EventDispatcher/EventDispatcher.h"

#include "Renderer/Framebuffer/Framebuffer.h"

#include "GLFW/glfw3.h"

namespace Volund
{
	struct WindowData
	{
		uint64_t Width = 0;
		uint64_t Height = 0;

		GLFWwindow* GlfwWindow;

		Ref<EventDispatcher> Dispatcher;
	};

	enum class CursorMode
	{
		Normal = GLFW_CURSOR_NORMAL,
		Hidden = GLFW_CURSOR_HIDDEN,
		Disabled = GLFW_CURSOR_DISABLED
	};

	class Window
	{
	public:

		void Update();

		GLFWwindow* GetGlfwWindow();

		void SetCursorMode(CursorMode newMode);

		void SetTitle(const std::string& title);

		void SetVsync(bool enabled);

		Vec2 GetSize();

		float GetAspectRatio();

		void Flush();

		void Reset();

		Window(Ref<EventDispatcher> dispatcher, uint64_t width, uint64_t height, bool fullScreen);

		~Window();

	private:

		Ref<WindowData> m_WindowData;

	};

}
