#pragma once

#include "Widget/Widget.h"

class AssetsWidget : public Widget
{
public:

	const char* GetName() override;

	void OnUpdate() override;

	AssetsWidget(Volund::Layer* Parent);

private:

	void DrawAssetTab(Volund::Ref<Volund::Scene> Scene);

	void DrawFileExplorer(Volund::Ref<Volund::Scene> Scene);

	void DrawDirectory(Volund::Ref<Volund::Scene> Scene, std::filesystem::path DirectoryPath);
};

