#pragma once

class ViewportCamera
{
public:

	float LookSpeed = 1.0f;
	float MoveSpeed = 2.5f;
	float ZoomSpeed = 0.2f;

	float FOV = 80.0f;

	VL::Ref<VL::Framebuffer> GetSceneFramebuffer();
	VL::Ref<VL::Framebuffer> GetEditorFramebuffer();

	void Update(VL::Input& input, float timeStep, bool isInWindow);

	void Render(VL::Ref<VL::GameState> gameState, ImVec2 viewportSize);

	void Invalidate();

	ViewportCamera();

private:

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
	VL::Ref<VL::Framebuffer> m_EntityPickFramebuffer;
};