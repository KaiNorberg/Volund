#pragma once

#include "EventDispatcher/EventDispatcher.h"

namespace Volund
{
    struct WindowData
    {
        uint64_t Width = 0;
        uint64_t Height = 0;

        bool FullScreen = false;

        bool CaptureMouse = false;
        bool ShowMouse = true;

        Ref<EventDispatcher> Dispatcher = nullptr;
    };

    class Window
    {
    public:

        void SwapBuffers();

        void Update();

        void SetFocus();

        void SetCursorMode(std::string const& NewMode);

        void SetTitle(std::string const& Title);

        Vec2 GetSize();

        float GetAspectRatio();

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