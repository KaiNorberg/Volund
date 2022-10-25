#pragma once

#include "Widget/Widget.h"

class AssetWidget : public Widget
{
public:

	const char* GetName() override;

	void Draw(VL::TimeStep TS) override;

	using Widget::Widget;

private:

	void DrawResource(const VL::Resource* Resource);

	void DrawDirectory(const std::filesystem::path& Directory);

	void HandleResourceEntry(const std::string& Name, const VL::Resource* Resource);

	void HandleDirectoryEntry(const std::filesystem::directory_entry& Entry);
};

