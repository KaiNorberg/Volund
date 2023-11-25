#pragma once

#include "../EditorWindow.h"

class ViewportWindow : public EditorWindow
{
public:

	float LookSpeed = 1.0f;
	float MoveSpeed = 2.5f;
	float ZoomSpeed = 0.2f;

	float FOV = 80.0f;

	void OnProcedure(const VL::Event& e) override;

	ViewportWindow(VL::Ref<EditorContext> context);

private:
	
	void UpdateCameraMovement(VL::Input& input, float timeStep, bool isInWindow);

	void Render(VL::Ref<VL::GameState> gameState, ImVec2 viewportSize);

	VL::Vec2 m_FramebufferSize = VL::Vec2(100, 100);

	VL::Input m_Input;

	VL::Ref<VL::Texture> m_PlayIcon;
	VL::Ref<VL::Texture> m_PauseIcon;

	VL::Ref<VL::Framebuffer> m_Viewportbuffer;

	VL::Vec3 m_Position;
	VL::Vec3 m_BallCenter;
	VL::Vec3 m_Rotation;
	float m_Distance;

	VL::IVec2 m_OldMousePosition;
	float m_OldScrollPosition;

	VL::Ref<VL::Renderer> m_Renderer;

	VL::Ref<VL::Effect> m_GridEffect;

	VL::Ref<VL::Framebuffer> m_SceneFramebuffer;
	VL::Ref<VL::Framebuffer> m_EditorFramebuffer;
};

