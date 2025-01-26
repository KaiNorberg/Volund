#pragma once

#include "Panel.hpp"

class Explorer : public Panel
{
public:
    void OnProcedure(const VL::Event& e);
    Explorer(std::shared_ptr<EditorContext> context);
private:
    void Render();
    void ImGuiFilesystemEntry(std::string const& payloadPath, std::string const& name, bool isDirectory);
    float m_padding = 16.0f;
    float m_thumbnailSize = 64.0f;
    std::shared_ptr<VL::Texture> m_directoryIcon;
    std::shared_ptr<VL::Texture> m_fileIcon;
    std::filesystem::path m_cwd;
    std::filesystem::path m_oldCwd;
    bool m_resourcesOpen = false;
};
