#pragma once

#include "Panel.h"

#include <imgui.h>

class Viewport : public Panel
{
public:

    float LookSpeed = 1.0f;
    float MoveSpeed = 2.5f;
    float ZoomSpeed = 0.2f;

    float FOV = 80.0f;

    void OnProcedure(const VL::Event& e) override;

    Viewport(std::shared_ptr<EditorContext> context);

private:

    void UpdateCameraMovement(float timeStep, bool isWindowHovered);

    void Render(std::shared_ptr<VL::GameState> gameState, ImVec2 viewportSize);

    VL::Vec2 m_FramebufferSize = VL::Vec2(100, 100);

    VL::Input m_Input;

    std::shared_ptr<VL::Texture> m_PlayIcon;
    std::shared_ptr<VL::Texture> m_PauseIcon;

    std::shared_ptr<VL::Framebuffer> m_Viewportbuffer;

    VL::Vec3 m_Position;
    VL::Vec3 m_BallCenter;
    VL::Vec3 m_Rotation;
    float m_Distance;

    VL::IVec2 m_OldMousePosition;
    float m_OldScrollPosition;

    std::shared_ptr<VL::Renderer> m_Renderer;

    std::shared_ptr<VL::Effect> m_GridEffect;

    std::shared_ptr<VL::Framebuffer> m_SceneFramebuffer;
    std::shared_ptr<VL::Framebuffer> m_EditorFramebuffer;
};
