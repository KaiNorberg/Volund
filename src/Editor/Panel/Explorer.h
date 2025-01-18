#pragma once

#include "Panel.h"

class Explorer : public Panel
{
public:

    void OnProcedure(const VL::Event& e);

    Explorer(std::shared_ptr<EditorContext> context);

private:

    float m_padding = 16.0f;
    float m_thumbnailSize = 64.0f;

    std::shared_ptr<VL::Texture> m_directoryIcon;
    std::shared_ptr<VL::Texture> m_fileIcon;

    std::filesystem::path m_currentDirectory;
    std::filesystem::path m_oldParentDir;

    bool m_resourcesOpen = false;

    void ImGuiFilesystemEntry(std::string const& payloadPath, std::string const& name, bool isDirectory);
};
