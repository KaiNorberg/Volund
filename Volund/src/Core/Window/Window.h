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

		static void Update();

		static void SetProcedureCatch(ProcCatch ProcedureCatch);

		static void SetCursorMode(CursorMode NewMode);

		static void SetTitle(std::string_view Title);

		static void SetVsync(bool Enabled);

		static void SetFocus();

		static Vec2 GetSize();

		static float GetAspectRatio();

		static void* GetInstance();

		static void* GetHandle();

		static void* GetDeviceContext();

		static void Show();

		static void Flush();

		static void Reset();

		static void Create(uint64_t Width, uint64_t Height, bool FullScreen);

		static void Destroy();

	private:

		Window() = default;

		~Window();

		static inline WindowData _Data;
	};

} //namespace Volund
