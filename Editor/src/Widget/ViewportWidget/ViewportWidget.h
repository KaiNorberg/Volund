#pragma once

#include "Widget/Widget.h"

class ViewportWidget : public Widget
{
public:

	const char* GetName() override;

	void OnKey(const VL::Event& e) override;

	void OnRender() override;

	ViewportWidget(VL::Application* app);

private:

	VL::Input m_Input;
};

