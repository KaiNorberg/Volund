#pragma once

#include "Widget/Widget.h"

class EntitiesWidget : public Widget
{
public:

	const char* GetName() override;

	void Draw(VL::TimeStep TS) override;

	using Widget::Widget;

private:

	bool DrawEntityNode(VL::Ref<VL::Scene> Scene, VL::Entity Entity, const std::string& EntityName);
};

