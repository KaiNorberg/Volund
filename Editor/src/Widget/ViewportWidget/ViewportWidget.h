#pragma once

#include "Widget/Widget.h"

class ViewportWidget : public Widget
{
public:

	const char* GetName() override;

	void OnUpdate() override;

	ViewportWidget(Volund::Layer* Parent);

private:

	Volund::Ref<Volund::Framebuffer> _Framebuffer;

};

