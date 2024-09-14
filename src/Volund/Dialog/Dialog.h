#pragma once

#include "Window/Window.h"

namespace Volund
{
    class Dialog
    {
    public:

        static std::string InputBox(const std::string& title, const std::string& message, const std::string& defaultInput = "");

        static std::string OpenFolder(std::shared_ptr<Window> window);

        static std::string OpenFile(std::shared_ptr<Window> window);

        static void Message(const std::string& title, const std::string& message, const std::string& dialogType, const std::string& iconType);

    private:
    };
}
