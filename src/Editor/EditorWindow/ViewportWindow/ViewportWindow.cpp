#include "ViewportWindow.h"

#include <imgui.h>

void ViewportWindow::OnProcedure(const VL::Event& e)
{
	this->m_Input.Procedure(e);

	switch (e.Type)
	{
	case VOLUND_EVENT_TYPE_RENDER:
	{
		auto gameState = this->m_Context->GameState;

		this->Render(gameState, ImVec2(this->m_FramebufferSize.x, this->m_FramebufferSize.y));

		ImVec2 buttonSize = ImVec2(ImGui::GetTextLineHeight(), ImGui::GetTextLineHeight());
		bool isPaused = this->m_Context->IsPaused();

		ImGuiAlign("#######", 1.f);

		ImGui::BeginDisabled(!isPaused);
		if (ImGui::ImageButton("PlayButton", (ImTextureID)this->m_PlayIcon->GetID(),
			buttonSize, ImVec2(0, 1), ImVec2(1, 0)))
		{
			if (this->m_Context->IsPaused())
			{
				this->m_Context->Enqueue(EDITOR_EVENT_TYPE_PLAY);
			}
		}
		ImGui::EndDisabled();

		ImGui::SameLine();

		ImGui::BeginDisabled(isPaused);
		if (ImGui::ImageButton("PauseButton", (ImTextureID)this->m_PauseIcon->GetID(),
			buttonSize, ImVec2(0, 1), ImVec2(1, 0)))
		{
			if (!this->m_Context->IsPaused())
			{
				this->m_Context->Enqueue(EDITOR_EVENT_TYPE_PAUSE);
			}
		}
		ImGui::EndDisabled();

		if (ImGui::BeginChild(this->GetId().c_str()))
		{
			ImVec2 viewportSize = ImGui::GetContentRegionAvail();
			this->m_FramebufferSize = VL::Vec2(viewportSize.x, viewportSize.y);
			ImVec2 cursorPosition = ImGui::GetCursorScreenPos();

			if (!this->m_Context->IsPaused())
			{
				ImGui::Image(reinterpret_cast<void*>((uint64_t)this->m_SceneFramebuffer->GetAttachment(0)), ImVec2(this->m_FramebufferSize.x, this->m_FramebufferSize.y), ImVec2(0, 1), ImVec2(1, 0));
			}
			else
			{
				ImGui::Image(reinterpret_cast<void*>((uint64_t)this->m_EditorFramebuffer->GetAttachment(0)), ImVec2(this->m_FramebufferSize.x, this->m_FramebufferSize.y), ImVec2(0, 1), ImVec2(1, 0));
			}
		}
		ImGui::EndChild();
	}
	break;
	case VOLUND_EVENT_TYPE_UPDATE:
	{
		float timeStep = VOLUND_EVENT_UPDATE_GET_TIMESTEP(e);

		this->UpdateCameraMovement(this->m_Input, timeStep, this->IsWindowHovered());
	}
	break;
	case EDITOR_EVENT_TYPE_RESET:
	{
		this->m_EditorFramebuffer->Invalidate();
		this->m_SceneFramebuffer->Invalidate();
	}
	break;
	}
}

void ViewportWindow::UpdateCameraMovement(VL::Input& input, float timeStep, bool isInWindow)
{
	VL::IVec2 cursorDelta = input.GetMousePosition() - this->m_OldMousePosition;
	float scrollDelta = input.GetScrollPosition() - this->m_OldScrollPosition;
	cursorDelta.x = std::clamp(cursorDelta.x, -10, 10);
	cursorDelta.y = std::clamp(cursorDelta.y, -10, 10);
	scrollDelta = std::clamp(scrollDelta, -10.0f, 10.0f);

	if (isInWindow && input.IsMouseButtonHeld(VOLUND_MOUSE_BUTTON_RIGHT))
	{
		if (scrollDelta != 0.0f)
		{
			this->m_Distance -= (scrollDelta)*this->ZoomSpeed * this->m_Distance;
		}

		VL::Quat quaternion = VL::Quat(VL::Math::Radians(this->m_Rotation));

		VL::Vec3 front = quaternion * VL::Math::BACK;
		VL::Vec3 right = quaternion * VL::Math::RIGHT;

		if (input.IsHeld('W'))
		{
			this->m_BallCenter += VL::Math::Normalize(VL::Vec3(front.x, 0.0, front.z)) * float(timeStep) * this->MoveSpeed * this->m_Distance;
		}
		if (input.IsHeld('S'))
		{
			this->m_BallCenter -= VL::Math::Normalize(VL::Vec3(front.x, 0.0, front.z)) * float(timeStep) * this->MoveSpeed * this->m_Distance;
		}
		if (input.IsHeld('A'))
		{
			this->m_BallCenter -= VL::Math::Normalize(VL::Vec3(right.x, 0.0, right.z)) * float(timeStep) * this->MoveSpeed * this->m_Distance;
		}
		if (input.IsHeld('D'))
		{
			this->m_BallCenter += VL::Math::Normalize(VL::Vec3(right.x, 0.0, right.z)) * float(timeStep) * this->MoveSpeed * this->m_Distance;
		}
		if (input.IsHeld(VOLUND_KEY_SPACE))
		{
			this->m_BallCenter += VL::Math::UP * float(timeStep) * this->MoveSpeed * this->m_Distance;
		}
		if (input.IsHeld(VOLUND_KEY_SHIFT))
		{
			this->m_BallCenter -= VL::Math::UP * float(timeStep) * this->MoveSpeed * this->m_Distance;
		}

		this->m_Rotation += VL::Vec3(-cursorDelta.y, -cursorDelta.x, 0.0f) * this->LookSpeed;
		this->m_Rotation.x = std::clamp(this->m_Rotation.x, -89.9f, 89.9f);

		this->m_Position = this->m_BallCenter - front * this->m_Distance;
	}

	this->m_OldScrollPosition = input.GetScrollPosition();
	this->m_OldMousePosition = input.GetMousePosition();
}

void ViewportWindow::Render(VL::Ref<VL::GameState> gameState, ImVec2 viewportSize)
{
	auto spec = this->m_SceneFramebuffer->GetSpec();
	if (viewportSize.x != spec.Width || viewportSize.y != spec.Height)
	{
		spec.Width = std::clamp((uint32_t)viewportSize.x, (uint32_t)1, (uint32_t)8000);
		spec.Height = std::clamp((uint32_t)viewportSize.y, (uint32_t)1, (uint32_t)8000);

		this->m_SceneFramebuffer->SetSpec(spec);
		this->m_EditorFramebuffer->SetSpec(spec);
	}

	VL::Vec3 front = VL::Math::Normalize(this->m_BallCenter - this->m_Position);
	VL::Mat4x4 viewMatrix = VL::Math::ViewMatrix(this->m_Position, this->m_Position + front, VL::Math::UP * -1);
	VL::Mat4x4 projectionMatrix = VL::Math::ProjectionMatrix(this->FOV, (float)spec.Width / (float)spec.Height, 0.1f, 1000.0f);

	VL::RendererEye editorEye;
	editorEye.ProjectionMatrix = projectionMatrix;
	editorEye.ViewMatrix = viewMatrix;
	editorEye.Target = this->m_EditorFramebuffer;
	editorEye.LayerMask = -1;
	editorEye.Effects.push_back(this->m_GridEffect);

	this->m_Renderer->Begin();
	this->m_Renderer->Submit(gameState, this->m_SceneFramebuffer);
	this->m_Renderer->Submit(editorEye);
	this->m_Renderer->End();
}

ViewportWindow::ViewportWindow(VL::Ref<EditorContext> context)
{
	this->SetName("Viewport");

	this->m_Context = context;

	this->m_PlayIcon = VL::Texture::Create("data/icons/play.png");
	this->m_PauseIcon = VL::Texture::Create("data/icons/pause.png");

	VL::FramebufferSpec spec;
	spec.ColorAttachments = { VL::TextureSpec(VL::TextureFormat::RGBA16F) };
	spec.DepthAttachment = VL::TextureSpec(VL::TextureFormat::Depth24Stencil8);
	spec.Height = 1080;
	spec.Width = 1920;

	this->m_SceneFramebuffer = VL::Framebuffer::Create(spec);
	this->m_EditorFramebuffer = VL::Framebuffer::Create(spec);

	this->m_Renderer = VL::ForwardRenderer::Create();

	this->m_BallCenter = VL::Vec3(0, 1, 0);
	this->m_Distance = 10.0f;

	this->m_Position = this->m_BallCenter + VL::Vec3(0.0, 0.0, 1.0) * this->m_Distance;
	this->m_Rotation = VL::Vec3(0.0, 0.0, 0.0);

	this->m_GridEffect = VL::Effect::Create(VL::Shader::Create("data/shaders/grid.shader"));
}
