#pragma once

#include "EventDispatcher/EventDispatcher.h"

namespace Volund
{
    struct WindowData
    {
        uint64_t Width;
        uint64_t Height;

        bool CaptureMouse;

        Ref<EventDispatcher> Dispatcher;
    };
    class Window
    {
    public:

        void SwapBuffers();

        void Update();

        void SetCursorMode(std::string const& NewMode);

        void SetTitle(std::string const& Title);

        Vec2 GetSize();

        void* GetDeviceContext();

        Window(Ref<EventDispatcher>& Dispatcher, uint64_t Width, uint64_t Height, bool FullScreen);

        ~Window();

    private:

        std::wstring ConvertToWString(std::string const& String);

        void* _Handle = nullptr;

        void* _Instance = nullptr;

        void* _DeviceContext = nullptr;

        WindowData _Data;
    };

} //namespace Volund