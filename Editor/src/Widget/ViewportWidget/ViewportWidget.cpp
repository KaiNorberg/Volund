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

void ViewportWidget::OnEvent(Event* E)
{
	this->_Input.HandleEvent(E);
}

void ViewportWidget::OnUpdate(TimeStep TS)
{
	this->MoveEye(TS);
	
	this->DrawViewport(TS);
}

ViewportWidget::ViewportWidget(Volund::Layer* Parent)
{
	this->_Parent = Parent;

	Volund::FramebufferSpec Spec;
	Spec.Height = 1080;
	Spec.Width = 1980;
	this->_Framebuffer = Volund::Framebuffer::Create(Spec);
}

void ViewportWidget::MoveEye(Volund::TimeStep TS)
{
	if (this->_Input.IsMouseButtonHeld(VOLUND_MOUSE_BUTTON_RIGHT))
	{
		Quat EyeQuaternion = Quat(Math::ToRadians(this->_Eye.Rotation));

		if (_Input.IsHeld('W'))
		{
			_Eye.Position += EyeQuaternion * Math::Back * this->_Eye.Speed * float(TS);
		}
		if (_Input.IsHeld('S'))
		{
			_Eye.Position += EyeQuaternion * Math::Forward * this->_Eye.Speed * float(TS);
		}
		if (_Input.IsHeld('A'))
		{
			_Eye.Position += EyeQuaternion * Math::Left * this->_Eye.Speed * float(TS);
		}
		if (_Input.IsHeld('D'))
		{
			_Eye.Position += EyeQuaternion * Math::Right * this->_Eye.Speed * float(TS);
		}

		IVec2 Delta = _Input.GetMousePosition() - this->_OldMousePosition;

		this->_Eye.Rotation -= Vec3(Delta.y, Delta.x, 0.0f) * this->_Eye.Sensitivity;
		this->_Eye.Rotation.x = Math::Clamp(this->_Eye.Rotation.x, -89.0f, 89.0f);
	}
	else if (this->_Input.IsMouseButtonHeld(VOLUND_MOUSE_BUTTON_MIDDLE))
	{
		Quat EyeQuaternion = Quat(Math::ToRadians(this->_Eye.Rotation));

		IVec2 Delta = _Input.GetMousePosition() - this->_OldMousePosition;

		this->_Eye.Position += EyeQuaternion * -Math::Right * (float)Delta.x * this->_Eye.DragSpeed + EyeQuaternion * Math::Up * (float)Delta.y * this->_Eye.DragSpeed;
	}

	this->_OldMousePosition = _Input.GetMousePosition();
}

void ViewportWidget::DrawViewport(Volund::TimeStep TS)
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
		Quat EyeQuaternion = Quat(Math::ToRadians(this->_Eye.Rotation));
		Mat4x4 ViewProjMatrix = glm::perspective(glm::radians(70.0f), AspectRatio, 0.1f, 1000.0f) *
			glm::lookAt(this->_Eye.Position, this->_Eye.Position + EyeQuaternion * Math::Back, EyeQuaternion * Math::Up);

		this->_Framebuffer->Bind();
		API->Clear();
		API->SetViewPort(0, 0, FramebufferSpec.Width, FramebufferSpec.Height);

		Renderer::BeginScene(ViewProjMatrix, this->_Eye.Position);

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
