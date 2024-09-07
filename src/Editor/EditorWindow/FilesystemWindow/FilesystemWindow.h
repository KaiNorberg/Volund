#pragma once

#include "../EditorWindow.h"

class FilesystemWindow : public EditorWindow
{
public:

    void OnProcedure(const VL::Event& e);

    FilesystemWindow(VL::Ref<EditorContext> context);

private:

    float m_Padding = 16.0f;
    float m_ThumbnailSize = 64.0f;

    VL::Ref<VL::Texture> m_DirectoryIcon;
    VL::Ref<VL::Texture> m_FileIcon;

    fs::path m_CurrentDirectory;
    fs::path m_OldParentDir;

    bool m_ResourcesOpen = false;

    void ImGuiFilesystemEntry(const std::string& payloadPath, const std::string& name, bool IsDirectory);
};