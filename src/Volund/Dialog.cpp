#include "Dialog.h"

#include "tinyfiledialogs/tinyfiledialogs.c"
#include "tinyfiledialogs/tinyfiledialogs.h"

namespace Volund
{
    std::string Dialog::InputBox(std::string const& title, std::string const& message, std::string const& defaultInput)
    {
        const char* ret = tinyfd_inputBox(title.c_str(), message.c_str(), defaultInput.c_str());

        if (ret != nullptr)
        {
            return ret;
        }
        else
        {
            return "";
        }
    }

    std::string Dialog::OpenFolder(std::shared_ptr<Window> window)
    {
        bool cursorEnabled = window->IsCursorEnabled();

        window->SetCursorEnabled(true);
        const char* ret = tinyfd_selectFolderDialog("", std::filesystem::current_path().string().c_str());
        window->SetCursorEnabled(cursorEnabled);

        if (ret != nullptr)
        {
            return ret;
        }
        else
        {
            return "";
        }
    }

    std::string Dialog::OpenFile(std::shared_ptr<Window> window)
    {
        bool cursorEnabled = window->IsCursorEnabled();

        window->SetCursorEnabled(true);
        
        const char* ret = tinyfd_openFileDialog("", std::filesystem::current_path().string().c_str(), 0, 0, "", 0);
        window->SetCursorEnabled(cursorEnabled);

        if (ret != nullptr)
        {
            return ret;
        }
        else
        {
            return "";
        }
    }

    void Dialog::Message(std::string const& title, std::string const& message,  std::string const& dialogType, std::string const& iconType)
    {
        tinyfd_messageBox(title.c_str(), message.c_str(), dialogType.c_str(), iconType.c_str(), 1);
    }

}
