#include "PCH/PCH.h"

#include "ViewportWidget.h"

#include "Editor/EditorModule/EditorModule.h"

const char* ViewportWidget::GetName()
{
	return "Viewport";
}

void ViewportWidget::Procedure(const VL::Event& e)
{
	this->m_Camera.Procedure(e);

	switch (e.Type)
	{
	case VL::EventType::Render:
	{
		const auto editorModule = this->m_App->GetModule<EditorModule>();
		auto window = this->m_App->GetModule<VL::WindowModule>()->GetWindow();

		if (ImGui::Begin(this->GetName(), &this->IsActive))
		{
			auto scene = editorModule->GetScene();
			if (scene != nullptr)
			{
				ImGui::SameLine();

				if (ImGui::BeginChild("ViewPort"))
				{
					ImVec2 vMin = ImGui::GetWindowContentRegionMin();
					ImVec2 vMax = ImGui::GetWindowContentRegionMax();

					ImVec2 viewportSize = ImVec2(vMax.x - vMin.x, vMax.y - vMin.y);

					scene->ResizeTarget(viewportSize.x, viewportSize.y);

					auto spec = this->m_Camera.Framebuffer->GetSpec();

					if (viewportSize.x != spec.Width || viewportSize.y != spec.Height)
					{
						spec.Width = viewportSize.x;
						spec.Height = viewportSize.y;
						this->m_Camera.Framebuffer->SetSpec(spec);
					}

					VL::RendererEye eye;
					eye.Target = this->m_Camera.Framebuffer;
					eye.ProjectionMatrix = this->m_Camera.GetProjectionMatrix();
					eye.ViewMatrix = this->m_Camera.GetViewMatrix();
					eye.Position = this->m_Camera.Position;
					eye.LayerMask = -1;

					VL::Renderer::Submit(eye);

					ImGui::Image(reinterpret_cast<void*>(this->m_Camera.Framebuffer->GetAttachment(0)), viewportSize, ImVec2(0, 1), ImVec2(1, 0));

					ImGui::EndChild();
				}
			}
			else
			{
				ImGui::Text("No Scene Selected!");
			}
		}
		ImGui::End();
	}
	break;
	case VL::EventType::Update:
	{
	}
	break;
	}
}

ViewportWidget::ViewportWidget(VL::Application* app)
{
	this->m_App = app;

	VL::FramebufferSpec spec;
	spec.ColorAttachments = { VL::TextureSpec(VL::TextureFormat::RGBA16F) };
	spec.DepthAttachment = VL::TextureSpec(VL::TextureFormat::Depth24Stencil8);
	spec.Height = 1080;
	spec.Width = 1920;

	this->m_Camera.Framebuffer = VL::Framebuffer::Create(spec);
	this->m_Camera.Position = VL::Vec3(0, 2, 10);
	this->m_Camera.Rotation = VL::Vec3(0, 0, 0);
}

glm::mat4x4 ViewportWidget::ViewportCamera::GetViewMatrix()
{
	VL::Quat quaternion = VL::Quat(this->Rotation);
	VL::Vec3 front = quaternion * VL::Utils::BACK;
	VL::Vec3 up = quaternion * VL::Utils::UP;

	return glm::lookAt(this->Position, this->Position + front, up);
}

glm::mat4x4 ViewportWidget::ViewportCamera::GetProjectionMatrix()
{
	auto spec = this->Framebuffer->GetSpec();

	return glm::perspective(glm::radians(80.0f), (float)spec.Width / (float)spec.Height, 0.1f, 1000.0f);
}

VL::Vec3 ViewportWidget::ViewportCamera::GetFront()
{
	return VL::Vec3();
}

VL::Vec3 ViewportWidget::ViewportCamera::GetUp()
{
	return VL::Vec3();
}

VL::Vec3 ViewportWidget::ViewportCamera::GetRight()
{
	return VL::Vec3();
}

void ViewportWidget::ViewportCamera::Procedure(const VL::Event& e)
{
	/*if (m_Input.IsHeld('W'))
	{
		this->m_Camera.Position += entityTransform->GetFront() * float(ts) * this->Speed;
	}
	if (m_Input.IsHeld('S'))
	{
		this->m_Camera.Position -= entityTransform->GetFront() * float(ts) * this->Speed;
	}
	if (m_Input.IsHeld('A'))
	{
		this->m_Camera.Position -= entityTransform->GetRight() * float(ts) * this->Speed;
	}
	if (m_Input.IsHeld('D'))
	{
		this->m_Camera.Position += entityTransform->GetRight() * float(ts) * this->Speed;
	}

	VL::Vec2 delta = m_Input.GetMousePosition() - this->m_OldMousePosition;

	delta.x = ((float)VL::Utils::Clamp(delta.x, -10.0f, 10.0f) * this->Sensitivity);
	delta.y = ((float)VL::Utils::Clamp(delta.y, -10.0f, 10.0f) * this->Sensitivity);

	this->m_Camera.Rotation -= VL::Vec3(delta.y, delta.x, 0.0f) * this->Sensitivity;
	this->m_Camera.Rotation.x = VL::Utils::Clamp(this->m_Camera.Rotation.x, -89.0f, 89.0f);

	entityTransform->SetRotation(m_Rotation);
	this->m_OldMousePosition = m_Input.GetMousePosition();*/
}
