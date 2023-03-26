#pragma once

#include "EventDispatcher/EventDispatcher.h"

#include "Renderer/RenderingContext/RenderingContext.h"

#include "Renderer/Framebuffer/Framebuffer.h"

namespace Volund
{
	using ProcCatch = void*(*)(void*, uint32_t, uint64_t, uint64_t);

	struct WindowData
	{
		uint64_t Width = 0;
		uint64_t Height = 0;

		bool FullScreen = false;

		bool CaptureMouse = false;
		bool ShowMouse = true;

		void* Handle = nullptr;
		void* Instance = nullptr;
		void* DeviceContext = nullptr;

		ProcCatch ProcedureCatch = nullptr;

		Ref<EventDispatcher> Dispatcher;

		Ref<RenderingContext> Context;
	};

	enum class CursorMode
	{
		Normal,
		Hidden,
		Disabled,
		Captured
	};

	class Window
	{
	public:

		void Update();

		void SetProcedureCatch(ProcCatch procedureCatch);

		void SetCursorMode(CursorMode newMode);

		void SetTitle(std::string_view title);

		void SetVsync(bool enabled);

		void SetFocus();

		Vec2 GetSize();

		float GetAspectRatio();

		void* GetInstance();

		void* GetHandle();

		void* GetDeviceContext();

		void Show();

		void Flush();

		void Reset();

		Window(Ref<EventDispatcher> dispatcher, uint64_t width, uint64_t height, bool fullScreen);

		~Window();

	private:

		WindowData m_Data;
	};

}
