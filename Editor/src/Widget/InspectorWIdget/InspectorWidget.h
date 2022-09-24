#pragma once

#include "Project/Project.h"

#include "Widget/Widget.h"

class InspectorWidget : public Widget
{
public:

	const char* GetName() override;

	void OnUpdate(Volund::TimeStep TS) override;

	InspectorWidget(Volund::Layer* Parent);

private:

	void DrawComponents();

	void DrawAddComponents();

	void DrawComponentView(const std::vector<Volund::Ref<Volund::Component>>& ComponentView, std::string_view Name, std::function<void(Volund::Ref<Volund::Component>)> DrawFunction);
};

