#include "PCH/PCH.h"
#include "FileDialog.h"

#include <windows.h>
#include <shobjidl_core.h>

std::string FileDialog::OpenFolder()
{
    return OpenDialog(FOS_PICKFOLDERS);
}

std::string FileDialog::OpenFile()
{
	return OpenDialog();
}

std::string FileDialog::OpenDialog(FILEOPENDIALOGOPTIONS Options)
{
    std::string Output;

    IFileOpenDialog* pFileOpen;

    // Create the FileOpenDialog object.
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
        IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

    if (SUCCEEDED(hr))
    {
        // Show the Open dialog box.
        pFileOpen->SetOptions(Options);
        hr = pFileOpen->Show(NULL);

        // Get the file name from the dialog box.
        if (SUCCEEDED(hr))
        {
            IShellItem* pItem;
            hr = pFileOpen->GetResult(&pItem);
            if (SUCCEEDED(hr))
            {
                PWSTR pszFilePath;
                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                // Display the file name to the user.
                if (SUCCEEDED(hr))
                {
                    std::wstring Temp = pszFilePath;
                    Output = std::string(Temp.begin(), Temp.end());
                    CoTaskMemFree(pszFilePath);
                }
                pItem->Release();
            }
        }
        pFileOpen->Release();
    }
    CoUninitialize();

    return Output;
}
