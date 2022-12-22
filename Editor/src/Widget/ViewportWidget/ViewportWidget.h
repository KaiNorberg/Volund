#pragma once

#include "Widget/Widget.h"

class ViewportWidget : public Widget
{
public:

	const char* GetName();

	void OnEvent(VL::Event* E) override;

	void OnRender() override;

	ViewportWidget(VL::Application* App);

private:

	VL::Input _Input;
};

