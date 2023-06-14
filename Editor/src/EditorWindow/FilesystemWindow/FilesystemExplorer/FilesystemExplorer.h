#pragma once

#include "EditorContext/EditorContext.h"

class FilesystemExplorer : public VL::ImGuiObject
{
public:

	void Procedure(const VL::Event& e) override;

	FilesystemExplorer(VL::Ref<EditorContext> context);

private:

	float m_Padding = 16.0f;
	float m_ThumbnailSize = 64.0f;

	VL::Ref<VL::Texture> m_DirectoryIcon;
	VL::Ref<VL::Texture> m_FileIcon;

	std::filesystem::path m_RelativeDirectory;
	std::filesystem::path m_OldParentDir;

	VL::Ref<EditorContext> m_Context;

	void ImGuiDirectory(const std::filesystem::path& path, const char* name = nullptr);

	void ImGuiFile(const std::filesystem::path& path);
}; 