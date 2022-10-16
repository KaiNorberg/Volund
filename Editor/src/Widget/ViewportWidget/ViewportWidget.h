#pragma once

#include "Widget/Widget.h"

class ViewportWidget : public Widget
{
public:

	const char* GetName() override;

	void OnEvent(VL::Event* E) override;

	void Draw(VL::TimeStep TS) override;

	ViewportWidget(Editor* editor, bool Active = false);

private:

	void DrawSceneView(VL::TimeStep TS);

	void DrawGameView(VL::TimeStep TS, VL::Ref<VL::Scene> GameScene);

	void HandleSceneViewInput(VL::TimeStep TS);

	struct
	{
		float DragSpeed = 0.01f;

		float Speed = 10.0f;

		float Sensitivity = 0.5f;

		VL::Vec3 Position = VL::Vec3(0.0f, 2.0f, 10.0f);

		VL::Vec3 Rotation = VL::Vec3(0.0f);

	} _Eye;

	VL::Input _Input;

	VL::IVec2 _OldMousePosition = VL::IVec2(0);

	VL::Ref<VL::Framebuffer> _Framebuffer;

	VL::Ref<VL::Scene> _GameScene;

	int _GizmoOperation = 0;
};

