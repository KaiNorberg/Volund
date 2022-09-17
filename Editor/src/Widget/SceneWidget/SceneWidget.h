#pragma once

#include "Widget/Widget.h"

class SceneWidget : public Widget
{
public:

	const char* GetName() override;

	void OnUpdate() override;

	SceneWidget(Volund::Layer* Parent);

private:

	void DrawEntityTab(Volund::Ref<Volund::Scene> Scene);

	void DrawAssetTab(Volund::Ref<Volund::Scene> Scene);

	void DrawFileExplorer(Volund::Ref<Volund::Scene> Scene);

	void DrawDirectory(Volund::Ref<Volund::Scene> Scene, std::filesystem::path DirectoryPath);

	void DrawEntityNode(Volund::Ref<Volund::Entity> Entity);

	void DrawInspector(Volund::Ref<Volund::Entity> Entity, Volund::Ref<Volund::Scene> Scene);

	void DrawComponentView(const std::vector<Volund::Ref<Volund::Component>>& ComponentView, std::string_view Name, std::function<void(Volund::Ref<Volund::Component>)> DrawFunction);

	std::string _SelectedEntity;

};

