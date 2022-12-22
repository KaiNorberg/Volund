#pragma once

#include "Core/EventDispatcher/EventDispatcher.h"

#include "Renderer/Context/Context.h"

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

		void* _Handle = nullptr;
		void* _Instance = nullptr;
		void* _DeviceContext = nullptr;

		ProcCatch ProcedureCatch = nullptr;

		Ref<EventDispatcher> Dispatcher;

		Ref<Context> RenderingContext;
	};

	enum class CursorMode
	{
		NORMAL,
		HIDDEN,
		DISABLED,
		CAPTURED
	};

	class Window
	{
	public:

		void Update();

		void SetProcedureCatch(ProcCatch ProcedureCatch);

		void SetCursorMode(CursorMode NewMode);

		void SetTitle(std::string_view Title);

		void SetVsync(bool Enabled);

		void SetFocus();

		Vec2 GetSize();

		float GetAspectRatio();

		void* GetInstance();

		void* GetHandle();

		void* GetDeviceContext();

		void Show();

		void Flush();

		void Reset();

		Window(Ref<EventDispatcher> Dispatcher, uint64_t Width, uint64_t Height, bool FullScreen);

		~Window();

	private:

		WindowData _Data;
	};

}
