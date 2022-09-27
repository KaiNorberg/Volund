#pragma once

#include "Project/Project.h"

#include "Widget/Widget.h"

class InspectorWidget : public Widget
{
public:

	const char* GetName() override;

	void Draw(VL::TimeStep TS) override;

	using Widget::Widget;

private:

	void DrawComponents();

	void DrawAddComponents();

	void DrawComponentView(const std::vector<VL::Ref<VL::Component>>& ComponentView, std::string_view Name, std::function<void(VL::Ref<VL::Component>)> DrawFunction);
};

