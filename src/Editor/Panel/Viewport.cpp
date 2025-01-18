#include "Viewport.h"

#include "Utils.h"

#include <imgui.h>

void Viewport::OnProcedure(const VL::Event& e)
{
	this->m_input.Procedure(e);

	switch (e.type)
	{
	case VOLUND_EVENT_RENDER:
	{
		this->Render(this->m_context->state->SceneRef(), ImVec2(this->m_framebufferSize.x, this->m_framebufferSize.y));

		ImVec2 buttonSize = ImVec2(ImGui::GetTextLineHeight(), ImGui::GetTextLineHeight());
		bool isPaused = this->m_context->IsPaused();

		ImGuiAlign("#######", 1.f);

		ImGui::BeginDisabled(!isPaused);
		if (ImGui::ImageButton("PlayButton", (ImTextureID)this->m_playIcon->GetID(),
			buttonSize, ImVec2(0, 1), ImVec2(1, 0)))
		{
			if (this->m_context->IsPaused())
			{
				this->m_context->Enqueue(EDITOR_CMD_PLAY);
			}
		}
		ImGui::EndDisabled();

		ImGui::SameLine();

		ImGui::BeginDisabled(isPaused);
		if (ImGui::ImageButton("PauseButton", (ImTextureID)(uint64_t)this->m_pauseIcon->GetID(),
			buttonSize, ImVec2(0, 1), ImVec2(1, 0)))
		{
			if (!this->m_context->IsPaused())
			{
				this->m_context->Enqueue(EDITOR_CMD_PAUSE);
			}
		}
		ImGui::EndDisabled();

		if (ImGui::BeginChild(this->GetId().c_str()))
		{
			ImVec2 viewportSize = ImGui::GetContentRegionAvail();
			this->m_framebufferSize = VL::Vec2(viewportSize.x, viewportSize.y);
			ImVec2 cursorPosition = ImGui::GetCursorScreenPos();

			if (!this->m_context->IsPaused())
			{
				ImGui::Image(reinterpret_cast<void*>((uint64_t)this->m_sceneFramebuffer->GetAttachment(0)), ImVec2(this->m_framebufferSize.x, this->m_framebufferSize.y), ImVec2(0, 1), ImVec2(1, 0));
			}
			else
			{
				ImGui::Image(reinterpret_cast<void*>((uint64_t)this->m_editorFramebuffer->GetAttachment(0)), ImVec2(this->m_framebufferSize.x, this->m_framebufferSize.y), ImVec2(0, 1), ImVec2(1, 0));
			}
		}
		ImGui::EndChild();
	}
	break;
	case VOLUND_EVENT_UPDATE:
	{
		float timeStep = VOLUND_EVENT_UPDATE_GET_TIMESTEP(e);

		this->UpdateCameraMovement(timeStep, true);
	}
	break;
	case EDITOR_EVENT_RESET:
	{
		this->m_editorFramebuffer->Invalidate();
		this->m_sceneFramebuffer->Invalidate();
	}
	break;
	}
}

void Viewport::UpdateCameraMovement(float timeStep, bool isWindowHovered)
{
	VL::IVec2 cursorDelta = this->m_input.GetMousePosition() - this->m_oldMousePosition;
	float scrollDelta = this->m_input.GetScrollPosition() - this->m_oldScrollPosition;
	cursorDelta.x = std::clamp(cursorDelta.x, -10, 10);
	cursorDelta.y = std::clamp(cursorDelta.y, -10, 10);
	scrollDelta = std::clamp(scrollDelta, -10.0f, 10.0f);

	if (isWindowHovered && this->m_input.IsMouseButtonHeld(VOLUND_MOUSE_BUTTON_RIGHT))
	{
		if (scrollDelta != 0.0f)
		{
			this->m_distance -= (scrollDelta)*this->ZoomSpeed * this->m_distance;
		}

		VL::Quat quaternion = VL::Quat(VL::Math::Radians(this->m_rotation));

		VL::Vec3 front = quaternion * VL::Math::BACK;
		VL::Vec3 right = quaternion * VL::Math::RIGHT;

		if (this->m_input.IsHeld('W'))
		{
			this->m_ballCenter += VL::Math::Normalize(VL::Vec3(front.x, 0.0, front.z)) * float(timeStep) * this->MoveSpeed * this->m_distance;
		}
		if (this->m_input.IsHeld('S'))
		{
			this->m_ballCenter -= VL::Math::Normalize(VL::Vec3(front.x, 0.0, front.z)) * float(timeStep) * this->MoveSpeed * this->m_distance;
		}
		if (this->m_input.IsHeld('A'))
		{
			this->m_ballCenter -= VL::Math::Normalize(VL::Vec3(right.x, 0.0, right.z)) * float(timeStep) * this->MoveSpeed * this->m_distance;
		}
		if (this->m_input.IsHeld('D'))
		{
			this->m_ballCenter += VL::Math::Normalize(VL::Vec3(right.x, 0.0, right.z)) * float(timeStep) * this->MoveSpeed * this->m_distance;
		}
		if (this->m_input.IsHeld(VOLUND_KEY_SPACE))
		{
			this->m_ballCenter += VL::Math::UP * float(timeStep) * this->MoveSpeed * this->m_distance;
		}
		if (this->m_input.IsHeld(VOLUND_KEY_SHIFT))
		{
			this->m_ballCenter -= VL::Math::UP * float(timeStep) * this->MoveSpeed * this->m_distance;
		}

		this->m_rotation += VL::Vec3(-cursorDelta.y, -cursorDelta.x, 0.0f) * this->LookSpeed;
		this->m_rotation.x = std::clamp(this->m_rotation.x, -89.9f, 89.9f);

		this->m_position = this->m_ballCenter - front * this->m_distance;
	}

	this->m_oldScrollPosition = this->m_input.GetScrollPosition();
	this->m_oldMousePosition = this->m_input.GetMousePosition();
}

void Viewport::Render(std::shared_ptr<VL::Scene> scene, ImVec2 viewportSize)
{
	auto spec = this->m_sceneFramebuffer->GetSpec();
	if (viewportSize.x != spec.Width || viewportSize.y != spec.Height)
	{
		spec.Width = std::clamp((uint32_t)viewportSize.x, (uint32_t)1, (uint32_t)8000);
		spec.Height = std::clamp((uint32_t)viewportSize.y, (uint32_t)1, (uint32_t)8000);

		this->m_sceneFramebuffer->SetSpec(spec);
		this->m_editorFramebuffer->SetSpec(spec);
	}

	VL::Vec3 front = VL::Math::Normalize(this->m_ballCenter - this->m_position);
	VL::Mat4x4 viewMatrix = VL::Math::ViewMatrix(this->m_position, this->m_position + front, VL::Math::UP * -1);
	VL::Mat4x4 projectionMatrix = VL::Math::ProjectionMatrix(this->FOV, (float)spec.Width / (float)spec.Height, 0.1f, 1000.0f);

	VL::RendererEye editorEye;
	editorEye.ProjectionMatrix = projectionMatrix;
	editorEye.ViewMatrix = viewMatrix;
	editorEye.Target = this->m_editorFramebuffer;
	editorEye.LayerMask = -1;
	editorEye.Effects.push_back(this->m_gridEffect);

	this->m_renderer->Begin();
	this->m_renderer->Submit(scene, this->m_sceneFramebuffer);
	this->m_renderer->Submit(editorEye);
	this->m_renderer->End();
}

Viewport::Viewport(std::shared_ptr<EditorContext> context)
{
	this->SetName("Viewport");

	this->m_context = context;

	this->m_playIcon = VL::Texture::Create("data/icons/play.png");
	this->m_pauseIcon = VL::Texture::Create("data/icons/pause.png");

	VL::FramebufferSpec spec;
	spec.ColorAttachments = { VL::TextureSpec(VL::TextureFormat::RGBA16F) };
	spec.DepthAttachment = VL::TextureSpec(VL::TextureFormat::Depth24Stencil8);
	spec.Height = 1080;
	spec.Width = 1920;

	this->m_sceneFramebuffer = VL::Framebuffer::Create(spec);
	this->m_editorFramebuffer = VL::Framebuffer::Create(spec);

	this->m_renderer = VL::ForwardRenderer::Create();

	this->m_ballCenter = VL::Vec3(0, 1, 0);
	this->m_distance = 10.0f;

	this->m_position = this->m_ballCenter + VL::Vec3(0.0, 0.0, 1.0) * this->m_distance;
	this->m_rotation = VL::Vec3(0.0, 0.0, 0.0);

	this->m_gridEffect = VL::Effect::Create(VL::Shader::Create("data/shaders/grid.shader"));
}
