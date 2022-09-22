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

	if (Scene != nullptr)
	{
		auto Context = this->_Parent->GetLayer<EditorLayer>()->GetContext();
		auto API = this->_Parent->GetLayer<EditorLayer>()->GetAPI();

		auto FramebufferSpec = this->_Framebuffer->GetSpec();
		auto ViewportSize = ImGui::GetContentRegionAvail();

		float AspectRatio = (float)ViewportSize.x / (float)ViewportSize.y;
		Quat Quaternion = Quat(Math::ToRadians(this->_EyeRotation));
		Mat4x4 ViewProjMatrix = glm::perspective(glm::radians(70.0f), AspectRatio, 0.1f, 1000.0f) *
			glm::lookAt(this->_EyePosition, this->_EyePosition + Quaternion * Math::Back, Quaternion * Math::Up);

		this->_Framebuffer->Bind();
		API->Clear();
		API->SetViewPort(0, 0, FramebufferSpec.Width, FramebufferSpec.Height);

		Renderer::BeginScene(ViewProjMatrix, this->_EyePosition);

		Scene->OnUpdate(0.0f);

		Renderer::EndScene();

		this->_Framebuffer->Unbind();

		ImGui::Image((void*)this->_Framebuffer->GetColorAttachment(), ViewportSize, ImVec2(0, 1), ImVec2(1, 0));
	}
	else
	{
		ImGui::Text("No Scene Loaded!");
	}

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