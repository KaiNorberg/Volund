#include "PCH/PCH.h"
#include "ViewportWidget.h"

#include "UI/UI.h"
#include "Editor/Editor.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

const char* ViewportWidget::GetName()
{
	return "Viewport";
}

void ViewportWidget::OnEvent(VL::Event* E)
{
	this->_Input.HandleEvent(E);
}

void ViewportWidget::Draw(VL::TimeStep TS)
{
	this->MoveEye(TS);
	
	this->DrawViewport(TS);
}

ViewportWidget::ViewportWidget(UI* ui, bool Active)
	: Widget(ui, Active)
{
	VL::FramebufferSpec Spec;
	Spec.Height = 1080;
	Spec.Width = 1980;
	Spec.ColorAttachments = { VL::TextureFormat::RGBA8 };
	Spec.DepthAttachment = VL::TextureFormat::DEPTH24STENCIL8;
	this->_Framebuffer = VL::Framebuffer::Create(Spec);
}

void ViewportWidget::MoveEye(VL::TimeStep TS)
{
	if (this->_Input.IsMouseButtonHeld(VOLUND_MOUSE_BUTTON_RIGHT))
	{
		VL::Quat EyeQuaternion = VL::Quat(VL::Math::ToRadians(this->_Eye.Rotation));

		if (this->_Input.IsHeld('W'))
		{
			this->_Eye.Position += EyeQuaternion * VL::Math::Back * this->_Eye.Speed * float(TS);
		}
		if (this->_Input.IsHeld('S'))
		{
			this->_Eye.Position += EyeQuaternion * VL::Math::Forward * this->_Eye.Speed * float(TS);
		}
		if (this->_Input.IsHeld('A'))
		{
			this->_Eye.Position += EyeQuaternion * VL::Math::Left * this->_Eye.Speed * float(TS);
		}
		if (this->_Input.IsHeld('D'))
		{
			this->_Eye.Position += EyeQuaternion * VL::Math::Right * this->_Eye.Speed * float(TS);
		}

		VL::IVec2 Delta = _Input.GetMousePosition() - this->_OldMousePosition;

		this->_Eye.Rotation -= VL::Vec3(Delta.y, Delta.x, 0.0f) * this->_Eye.Sensitivity;
		this->_Eye.Rotation.x = VL::Math::Clamp(this->_Eye.Rotation.x, -89.0f, 89.0f);
	}
	else if (this->_Input.IsMouseButtonHeld(VOLUND_MOUSE_BUTTON_MIDDLE))
	{
		VL::Quat EyeQuaternion = VL::Quat(VL::Math::ToRadians(this->_Eye.Rotation));

		VL::IVec2 Delta = _Input.GetMousePosition() - this->_OldMousePosition;

		this->_Eye.Position += EyeQuaternion * -VL::Math::Right * (float)Delta.x * this->_Eye.DragSpeed + EyeQuaternion * VL::Math::Up * (float)Delta.y * this->_Eye.DragSpeed;
	}

	this->_OldMousePosition = _Input.GetMousePosition();
}

void ViewportWidget::DrawViewport(VL::TimeStep TS)
{
	ImGui::Begin("Viewport");

	auto Scene = this->_UI->GetProject()->GetScene();

	if (Scene != nullptr)
	{
		auto FramebufferSpec = this->_Framebuffer->GetSpec();
		auto ViewportSize = ImGui::GetContentRegionAvail();

		this->_Framebuffer->Bind();
		VL::RenderingAPI::Clear();
		VL::RenderingAPI::SetViewPort(0, 0, this->_Framebuffer->GetSpec().Width, this->_Framebuffer->GetSpec().Height);

		VL::Quat EyeQuaternion = VL::Quat(VL::Math::ToRadians(this->_Eye.Rotation));
		VL::Mat4x4 ViewMatrix = glm::lookAt(this->_Eye.Position, this->_Eye.Position + EyeQuaternion * VL::Math::Back, EyeQuaternion * VL::Math::Up);
		VL::Mat4x4 ProjectionMatrix = glm::perspective(glm::radians(70.0f), (float)ViewportSize.x / (float)ViewportSize.y, 0.1f, 1000.0f);
		VL::Renderer::Begin(ViewMatrix, ProjectionMatrix);

		Scene->OnUpdate(0.0f);

		Renderer::End();
		this->_Framebuffer->Unbind();

		ImGui::Image((void*)(uint64_t)this->_Framebuffer->GetAttachment(0), ViewportSize, ImVec2(0, 1), ImVec2(1, 0));
	}
	else
	{
		ImGui::Text("No Scene Loaded!");
	}

	ImGui::End();
}

