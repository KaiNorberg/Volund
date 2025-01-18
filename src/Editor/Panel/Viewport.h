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

    void Render(std::shared_ptr<VL::Scene> scene, ImVec2 viewportSize);

    VL::Vec2 m_framebufferSize = VL::Vec2(100, 100);

    VL::Input m_input;

    std::shared_ptr<VL::Texture> m_playIcon;
    std::shared_ptr<VL::Texture> m_pauseIcon;

    std::shared_ptr<VL::Framebuffer> m_viewportbuffer;

    VL::Vec3 m_position;
    VL::Vec3 m_ballCenter;
    VL::Vec3 m_rotation;
    float m_distance;

    VL::IVec2 m_oldMousePosition;
    float m_oldScrollPosition;

    std::shared_ptr<VL::Renderer> m_renderer;

    std::shared_ptr<VL::Effect> m_gridEffect;

    std::shared_ptr<VL::Framebuffer> m_sceneFramebuffer;
    std::shared_ptr<VL::Framebuffer> m_editorFramebuffer;
};
