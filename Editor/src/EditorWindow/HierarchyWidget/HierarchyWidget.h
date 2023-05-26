#pragma once

#include "Widget/Widget.h"

class HierarchyWidget : public Widget
{
public:

	const char* GetName() override;

	void Procedure(const VL::Event& e) override;

	HierarchyWidget(VL::Ref<EditorContext> context);

private:

	bool DrawEntityNode(VL::Entity Entity, const std::string& EntityName);
};
