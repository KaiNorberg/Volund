#pragma once

#include "Widget/Widget.h"

class ViewportWidget : public Widget
{
public:

	const char* GetName() override;

	void OnEvent(Volund::Event* E) override;

	void OnUpdate(Volund::TimeStep TS) override;

	ViewportWidget(Volund::Layer* Parent, bool Active = false);

private:

	void MoveEye(Volund::TimeStep TS);

	void DrawViewport(Volund::TimeStep TS);

	struct
	{
		float DragSpeed = 0.01f;

		float Speed = 10.0f;

		float Sensitivity = 0.5f;

		Volund::Vec3 Position = Volund::Vec3(0.0f, 2.0f, 10.0f);

		Volund::Vec3 Rotation = Volund::Vec3(0.0f);

	} _Eye;

	Volund::Input _Input;

	Volund::IVec2 _OldMousePosition = Volund::IVec2(0);

	Volund::Ref<Volund::Framebuffer> _Framebuffer;
};

