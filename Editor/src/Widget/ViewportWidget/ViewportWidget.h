#pragma once

#include "Widget/Widget.h"

class ViewportWidget : public Widget
{
public:

	const char* GetName();

	void OnEvent(VL::Event* E);

	void OnUpdate(VL::TimeStep TS);

	ViewportWidget();

private:

	VL::Input _Input;

	VL::Ref<VL::Framebuffer> _Framebuffer = nullptr;
};

