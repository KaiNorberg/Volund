#include "PCH/PCH.h"

#include "Dialog.h"

#include "tinyfiledialogs/tinyfiledialogs.c"
#include "tinyfiledialogs/tinyfiledialogs.h"

namespace Volund
{
    std::string Dialog::OpenFolder(Ref<Window> window)
    {        
        CursorMode oldMode = window->GetCursorMode();

        window->SetCursorMode(CursorMode::Normal);
        const char* ret = tinyfd_selectFolderDialog("", std::filesystem::current_path().c_str());
        window->SetCursorMode(oldMode);

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
        CursorMode oldMode = window->GetCursorMode();

        window->SetCursorMode(CursorMode::Normal);
        const char* ret = tinyfd_openFileDialog("", std::filesystem::current_path().c_str(), 0, 0, "", 0);
        window->SetCursorMode(oldMode);

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