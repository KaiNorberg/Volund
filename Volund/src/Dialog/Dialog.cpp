#include "PCH/PCH.h"

#include "Dialog.h"

#include "tinyfiledialogs/tinyfiledialogs.c"
#include "tinyfiledialogs/tinyfiledialogs.h"

namespace Volund
{
    std::string Dialog::InputBox(const std::string& title, const std::string& message, const std::string& defaultInput)
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

    std::string Dialog::OpenFolder(Ref<Window> window)
    {        
        bool cursorEnabled = window->IsCursorEnabled();

        window->SetCursorEnabled(true);
        const char* ret = tinyfd_selectFolderDialog("", fs::current_path().string().c_str());
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

    std::string Dialog::OpenFile(Ref<Window> window)
    {
        bool cursorEnabled = window->IsCursorEnabled();
        
        window->SetCursorEnabled(true);
        const char* ret = tinyfd_openFileDialog("", fs::current_path().string().c_str(), 0, 0, "", 0);
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
    
    void Dialog::Message(const std::string& title, const std::string& message,  const std::string& dialogType, const std::string& iconType)
    {
        tinyfd_messageBox(title.c_str(), message.c_str(), dialogType.c_str(), iconType.c_str(), 1);
    }

}