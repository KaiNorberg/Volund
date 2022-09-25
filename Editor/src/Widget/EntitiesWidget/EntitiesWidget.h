#pragma once

#include "Widget/Widget.h"

class EntitiesWidget : public Widget
{
public:

	const char* GetName() override;

	void OnUpdate(Volund::TimeStep TS) override;

	EntitiesWidget(Volund::Layer* Parent, bool Active = false);

private:

	bool DrawEntityNode(Volund::Ref<Volund::Scene> Scene, Volund::Entity Entity, const std::string& EntityName);
};

