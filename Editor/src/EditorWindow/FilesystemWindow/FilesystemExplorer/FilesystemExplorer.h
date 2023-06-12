#pragma once

#include "EditorContext/EditorContext.h"

class FilesystemExplorer : public VL::ImGuiObject
{
public:

	void Procedure(const VL::Event& e) override;

	FilesystemExplorer(VL::Ref<EditorContext> context);

private:

	VL::Ref<EditorContext> m_Context;

	void ImGuiDirectory(const std::filesystem::path& parentPath, const std::filesystem::path& path);

	void ImGuiFile(const std::filesystem::path& parentPath, const std::filesystem::path& path);
}; 