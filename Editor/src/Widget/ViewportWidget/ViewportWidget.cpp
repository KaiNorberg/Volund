#include "PCH/PCH.h"

#include "ViewportWidget.h"

#include "Editor/EditorModule/EditorModule.h"

const char* ViewportWidget::GetName()
{
	return "Viewport";
}

void ViewportWidget::Procedure(const VL::Event& e)
{
	this->m_Input.Procedure(e);

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
					ImVec2 viewportSize = ImGui::GetContentRegionAvail();

					scene->ResizeTarget(viewportSize.x, viewportSize.y);

					this->m_Camera.SubmitToRenderer(viewportSize);

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
		float timeStep = VOLUND_EVENT_UPDATE_GET_TIMESTEP(e);

		this->m_Camera.Update(this->m_Input, timeStep);
	}
	break;
	}
}

ViewportWidget::ViewportWidget(VL::Application* app)
{
	this->m_App = app;
}

////////////////////////////////////////////////////////////

void ViewportWidget::ViewportCamera::Update(VL::Input& input, float timeStep)
{
	VL::Quat quaternion = VL::Quat(glm::radians(this->m_Rotation));
	VL::Vec3 front = quaternion * VL::Utils::BACK;
	VL::Vec3 up = quaternion * VL::Utils::UP;
	VL::Vec3 right = quaternion * VL::Utils::RIGHT;

	VL::IVec2 cursorDelta = input.GetMousePosition() - this->m_OldMousePosition;
	float scrollDelta = input.GetScrollPosition() - this->m_OldScrollPosition;

	cursorDelta.x = VL::Utils::Clamp(cursorDelta.x, -10, 10);
	cursorDelta.y = VL::Utils::Clamp(cursorDelta.y, -10, 10);
	scrollDelta = VL::Utils::Clamp(scrollDelta, -10.0f, 10.0f);

	if (input.IsMouseButtonHeld(VOLUND_MOUSE_BUTTON_MIDDLE))
	{
		this->m_Position += (up * (float)cursorDelta.y - right * (float)cursorDelta.x) * (this->MoveSpeed / 200.0f);
	}
	else if (input.IsMouseButtonHeld(VOLUND_MOUSE_BUTTON_RIGHT))
	{
		if (input.IsHeld('W'))
		{
			this->m_Position += front * float(timeStep) * this->MoveSpeed;
		}
		if (input.IsHeld('S'))
		{
			this->m_Position -= front * float(timeStep) * this->MoveSpeed;
		}
		if (input.IsHeld('A'))
		{
			this->m_Position -= right * float(timeStep) * this->MoveSpeed;
		}
		if (input.IsHeld('D'))
		{
			this->m_Position += right * float(timeStep) * this->MoveSpeed;
		}

		this->m_Rotation -= VL::Vec3(cursorDelta.y, cursorDelta.x, 0.0f) * this->LookSpeed;
		this->m_Rotation.x = VL::Utils::Clamp(this->m_Rotation.x, -89.0f, 89.0f);
	}

	this->m_Position += (front * scrollDelta) * this->ZoomSpeed;

	this->m_OldScrollPosition = input.GetScrollPosition();
	this->m_OldMousePosition = input.GetMousePosition();
}

void ViewportWidget::ViewportCamera::SubmitToRenderer(ImVec2 viewportSize)
{
	auto spec = this->Framebuffer->GetSpec();

	if (viewportSize.x != spec.Width || viewportSize.y != spec.Height)
	{
		spec.Width = viewportSize.x;
		spec.Height = viewportSize.y;
		this->Framebuffer->SetSpec(spec);
	}

	VL::Quat quaternion = VL::Quat(glm::radians(this->m_Rotation));
	VL::Vec3 front = quaternion * VL::Utils::BACK;
	VL::Vec3 up = quaternion * VL::Utils::UP;

	VL::Mat4x4 viewMatrix = glm::lookAt(this->m_Position, this->m_Position + front, -up);
	VL::Mat4x4 projectionMatrix = glm::perspective(this->FOV, (float)spec.Width / (float)spec.Height, 0.1f, 1000.0f);

	VL::RendererEye eye;
	eye.Target = this->Framebuffer;
	eye.ProjectionMatrix = projectionMatrix;
	eye.ViewMatrix = viewMatrix;
	eye.Position = this->m_Position;
	eye.LayerMask = -1;

	VL::Renderer::Submit(eye);
}

ViewportWidget::ViewportCamera::ViewportCamera()
{
	VL::FramebufferSpec spec;
	spec.ColorAttachments = { VL::TextureSpec(VL::TextureFormat::RGBA16F) };
	spec.DepthAttachment = VL::TextureSpec(VL::TextureFormat::Depth24Stencil8);
	spec.Height = 1080;
	spec.Width = 1920;

	this->Framebuffer = VL::Framebuffer::Create(spec);
}
