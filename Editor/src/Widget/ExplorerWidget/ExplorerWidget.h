#pragma once

#include "Widget/Widget.h"

class ExplorerWidget : public Widget
{
public:

	const char* GetName() override;

	void Draw(VL::TimeStep TS) override;

	ExplorerWidget(Editor* editor, bool Active = false);

private:

	void BackgroundContextMenu();

	void EntryContextMenu();

	void DrawEntry(const std::string& Name, const std::filesystem::path& Path, bool IsDirectory);
	
	VL::Ref<VL::Texture> _FileIcon;
	VL::Ref<VL::Texture> _FolderIcon;

	std::filesystem::path _CurrentDirectory;

	std::filesystem::path _HoveredEntry;

};

