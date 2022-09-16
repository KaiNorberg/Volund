#pragma once

#include "Widget/Widget.h"

class SceneWidget : public Widget
{
public:

	const char* GetName() override;

	void OnUpdate() override;

	SceneWidget(Volund::Layer* Parent);

private:

	void DrawEntity(Volund::Ref<Volund::Entity> Entity);

	void DrawComponents(Volund::Ref<Volund::Entity> Entity);	
	
	std::string _SelectedEntity;

};

