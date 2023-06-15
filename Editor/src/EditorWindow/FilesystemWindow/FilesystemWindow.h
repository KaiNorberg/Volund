#pragma once

#include "../EditorWindow.h"

#include "EditorContext/EditorContext.h"

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

	std::filesystem::path m_CurrentDirectory;
	std::filesystem::path m_OldParentDir;

	bool m_ResourcesOpen = false;

	void ImGuiDirectory(const std::string& payloadPath, const std::string& name);

	void ImGuiFile(const std::string& payloadPath, const std::string& name);
};