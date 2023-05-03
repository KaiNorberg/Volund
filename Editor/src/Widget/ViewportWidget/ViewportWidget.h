#pragma once

#include "Widget/Widget.h"

class ViewportWidget : public Widget
{
public:

	const char* GetName() override;

	void Procedure(const VL::Event& e);

	ViewportWidget(VL::Application* app);

private:
	
	struct ViewportCamera
	{
		VL::Vec3 Position;
		VL::Vec3 Rotation;

		VL::Quat Quaternion;

		glm::mat4x4 GetViewMatrix();

		glm::mat4x4 GetProjectionMatrix();

		VL::Vec3 GetFront();

		VL::Vec3 GetUp();

		VL::Vec3 GetRight();

		void Procedure(const VL::Event& e);

		VL::Ref<VL::Framebuffer> Framebuffer;
	} m_Camera;

	VL::Input m_Input;
};

