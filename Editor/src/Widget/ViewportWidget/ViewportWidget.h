#pragma once

#include "Widget/Widget.h"

class ViewportWidget : public Widget
{
public:

	const char* GetName() override;

	void OnUpdate() override;

	ViewportWidget(Volund::Layer* Parent);

private:

	Volund::Vec3 _EyePosition = Volund::Vec3(0.0f, 2.0f, 10.0f);

	Volund::Vec3 _EyeRotation = Volund::Vec3(0.0f);

	Volund::Ref<Volund::Framebuffer> _Framebuffer;
};

