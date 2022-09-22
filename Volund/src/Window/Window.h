#pragma once

#include "EventDispatcher/EventDispatcher.h"

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

		ProcCatch ProcedureCatch = nullptr;

		Ref<EventDispatcher> Dispatcher = nullptr;
	};

	class Window
	{
	public:
		void SwapBuffers() const;

		void Update();

		void SetFocus() const;

		void SetCursorMode(std::string_view NewMode);

		void SetTitle(std::string_view Title);

		Vec2 GetSize() const;

		float GetAspectRatio() const;

		void SetProcedureCatch(ProcCatch ProcedureCatch);

		void* GetHandle() const;

		void* GetDeviceContext() const;

		Window(Ref<EventDispatcher> Dispatcher, uint64_t Width, uint64_t Height, bool FullScreen);

		~Window();

	private:
		std::wstring ConvertToWString(std::string_view String);

		void* _Handle = nullptr;

		void* _Instance = nullptr;

		void* _DeviceContext = nullptr;

		WindowData _Data;
	};
} //namespace Volund
