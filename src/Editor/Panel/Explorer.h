#pragma once

#include "Panel.h"

class Explorer : public Panel
{
public:

    void OnProcedure(const VL::Event& e);

    Explorer(std::shared_ptr<EditorContext> context);

private:

    float m_Padding = 16.0f;
    float m_ThumbnailSize = 64.0f;

    std::shared_ptr<VL::Texture> m_DirectoryIcon;
    std::shared_ptr<VL::Texture> m_FileIcon;

    std::filesystem::path m_CurrentDirectory;
    std::filesystem::path m_OldParentDir;

    bool m_ResourcesOpen = false;

    void ImGuiFilesystemEntry(const std::string& payloadPath, const std::string& name, bool IsDirectory);
};
