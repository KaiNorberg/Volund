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
	VL::IVec2 cursorDelta = input.GetMousePosition() - this->m_OldMousePosition;
	float scrollDelta = input.GetScrollPosition() - this->m_OldScrollPosition;
	cursorDelta.x = VL::Utils::Clamp(cursorDelta.x, -10, 10);
	cursorDelta.y = VL::Utils::Clamp(cursorDelta.y, -10, 10);
	scrollDelta = VL::Utils::Clamp(scrollDelta, -10.0f, 10.0f);

	if (input.IsMouseButtonHeld(VOLUND_MOUSE_BUTTON_RIGHT) || scrollDelta != 0.0f)
	{
		VL::Vec3 front = glm::normalize(this->m_BallCenter - this->m_Position);
		VL::Quat cameraQuaternion = glm::quatLookAt(front, -VL::Utils::UP);
		VL::Vec3 right = cameraQuaternion * VL::Utils::RIGHT;

		if (input.IsHeld('W'))
		{
			this->m_BallCenter += glm::normalize(VL::Vec3(front.x, 0.0, front.z)) * float(timeStep) * this->MoveSpeed * this->m_Distance;
		}
		if (input.IsHeld('S'))
		{
			this->m_BallCenter -= glm::normalize(VL::Vec3(front.x, 0.0, front.z)) * float(timeStep) * this->MoveSpeed * this->m_Distance;
		}
		if (input.IsHeld('A'))
		{
			this->m_BallCenter += glm::normalize(VL::Vec3(right.x, 0.0, right.z)) * float(timeStep) * this->MoveSpeed * this->m_Distance;
		}
		if (input.IsHeld('D'))
		{
			this->m_BallCenter -= glm::normalize(VL::Vec3(right.x, 0.0, right.z)) * float(timeStep) * this->MoveSpeed * this->m_Distance;
		}
		if (input.IsHeld(VOLUND_KEY_SPACE))
		{
			this->m_BallCenter += VL::Utils::UP * float(timeStep) * this->MoveSpeed * this->m_Distance;
		}
		if (input.IsHeld(VOLUND_KEY_SHIFT))
		{
			this->m_BallCenter -= VL::Utils::UP * float(timeStep) * this->MoveSpeed * this->m_Distance;
		}

		this->m_BallRotation -= VL::Vec3(cursorDelta.y, cursorDelta.x, 0.0f) * this->LookSpeed;
		this->m_BallRotation.x = VL::Utils::Clamp(this->m_BallRotation.x, -89.0f, 89.0f);

		VL::Quat ballQuaternion = VL::Quat(glm::radians(this->m_BallRotation));

		this->m_Rotation = glm::eulerAngles(cameraQuaternion);

		VL::Mat4x4 ballMatrix = VL::Mat4x4(1.0f);
		ballMatrix = glm::translate(ballMatrix, this->m_BallCenter);
		ballMatrix *= VL::Mat4x4(ballQuaternion);
		ballMatrix = glm::scale(ballMatrix, VL::Vec3(this->m_Distance));

		this->m_Distance -= (scrollDelta) * this->ZoomSpeed * this->m_Distance;

		this->m_Position = ballMatrix * VL::Vec4(0.0, 0.0, m_Distance, 1.0);
	}
	/*else if (input.IsMouseButtonHeld(VOLUND_MOUSE_BUTTON_RIGHT))
	{
		this->m_BallRotation -= VL::Vec3(cursorDelta.y, cursorDelta.x, 0.0f) * this->MoveSpeed;
		this->m_BallRotation.x = VL::Utils::Clamp(this->m_BallRotation.x, -89.0f, 89.0f);
	}*/

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

	VL::Vec3 front = glm::normalize(this->m_BallCenter - this->m_Position);

	VL::Mat4x4 viewMatrix = glm::lookAt(this->m_Position, this->m_Position + front, -VL::Utils::UP);
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
	this->m_BallCenter = VL::Vec3(0, 1, 0);
	this->m_BallRotation = VL::Vec3(0, 0, 0);
	this->m_Position = VL::Vec3(0, 1, 1);
	this->m_Distance = 1.0f;
}
