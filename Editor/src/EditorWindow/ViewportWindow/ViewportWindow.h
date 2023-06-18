#pragma once

#include "../EditorWindow.h"

#include "EditorContext/EditorContext.h"

class ViewportWindow : public EditorWindow
{
public:

	void OnProcedure(const VL::Event& e) override;

	ViewportWindow(VL::Ref<EditorContext> context);

private:
	
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

		void Render(VL::Ref<VL::Scene> scene, ImVec2 viewportSize);

		ViewportCamera();

	private:

		VL::Vec3 m_Position;
		VL::Vec3 m_Rotation;
		VL::Vec3 m_BallCenter;
		VL::Vec3 m_BallRotation;
		float m_Distance;

		VL::IVec2 m_OldMousePosition;
		float m_OldScrollPosition;

		VL::Ref<VL::Renderer> m_Renderer;

		VL::Ref<VL::Framebuffer> m_SceneFramebuffer;
		VL::Ref<VL::Framebuffer> m_EditorFramebuffer;
	} m_Camera;

	VL::Vec2 m_Size = VL::Vec2(100, 100);
	std::string m_Text;
	VL::Ref<VL::Framebuffer> m_Viewportbuffer;

	VL::Ref<VL::Texture> m_PlayIcon;
	VL::Ref<VL::Texture> m_PauseIcon;

	//VL::Ref<VL::Texture> m_DisabledPlayIcon;
	//VL::Ref<VL::Texture> m_DisabledPauseIcon;

	VL::Input m_Input;
};

