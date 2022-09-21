#include "PCH/PCH.h"
#include "ViewportWidget.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

#include "Editor/EditorLayer/EditorLayer.h"

const char* ViewportWidget::GetName()
{
	return "Viewport";
}

void ViewportWidget::OnUpdate()
{
	ImGui::Begin("Viewport");

	auto Scene = this->_Parent->GetLayer<EditorLayer>()->GetScene();
	auto Context = this->_Parent->GetLayer<EditorLayer>()->GetContext();
	auto API = this->_Parent->GetLayer<EditorLayer>()->GetAPI();

	auto FramebufferSpec = this->_Framebuffer->GetSpec();
	auto ViewportSize = ImGui::GetContentRegionAvail();

	Camera* ActiveCamera = Camera::GetActiveCamera(Scene);

	if (ActiveCamera != nullptr)
	{
		float AspectRatio = (float)ViewportSize.x / (float)ViewportSize.y;
		Mat4x4 ViewProjMatrix = ActiveCamera->GetProjectionMatrix(AspectRatio) * ActiveCamera->GetViewMatrix();
		Vec3 EyePosition = ActiveCamera->GetEntity()->GetComponent<Transform>()->Position;
		auto& PointLights = Scene->ComponentView<PointLight>();

		this->_Framebuffer->Bind();
		API->Clear();
		API->SetViewPort(0, 0, FramebufferSpec.Width, FramebufferSpec.Height);

		Renderer::BeginScene(ViewProjMatrix, EyePosition, PointLights);

		if (Scene != nullptr)
		{
			Scene->OnUpdate(0.0f);
		}

		Renderer::EndScene();

		this->_Framebuffer->Unbind();
	}
	else
	{
		if (Scene != nullptr)
		{
			Scene->OnUpdate(0.0f);
		}
	}

	ImGui::Image((void*)this->_Framebuffer->GetColorAttachment(), ViewportSize, ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();
}

ViewportWidget::ViewportWidget(Volund::Layer* Parent)
{
	this->_Parent = Parent;

	Volund::FramebufferSpec Spec;
	Spec.Height = 1080;
	Spec.Width = 1980;
	this->_Framebuffer = Volund::Framebuffer::Create(Spec);
}