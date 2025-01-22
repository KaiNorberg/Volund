#pragma once

#include "Window.h"

#include <string>
#include <memory>

namespace Volund
{
    class VOLUND_API Dialog
    {
    public:
        static std::string InputBox(std::string const& title, std::string const& message, std::string const& defaultInput = "");
        static std::string OpenFolder(std::shared_ptr<Window> window);
        static std::string OpenFile(std::shared_ptr<Window> window);
        static void Message(std::string const& title, std::string const& message, std::string const& dialogType, std::string const& iconType);
    private:
    };
}
