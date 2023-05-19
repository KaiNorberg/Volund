#pragma once

#include "Widget/Widget.h"

class ViewportWidget : public Widget
{
public:

	const char* GetName() override;

	void Procedure(const VL::Event& e);

	ViewportWidget(VL::Application* app);

private:
	
	class ViewportCamera
	{
	public:

		float MoveSpeed = 10.0f;
		float ZoomSpeed = 1.0f;
		float LookSpeed = 1.0f;

		float FOV = 80.0f;

		VL::Ref<VL::Framebuffer> Framebuffer;

		void Update(VL::Input& input, float timeStep);

		void SubmitToRenderer(ImVec2 viewportSize);

		ViewportCamera();

	private:

		VL::Vec3 m_Position = VL::Vec3(0, 1, 0);
		VL::Vec3 m_Rotation = VL::Vec3(0, 0, 0);

		float m_OldScrollPosition;
		VL::IVec2 m_OldMousePosition;
	} m_Camera;

	VL::Input m_Input;
};

