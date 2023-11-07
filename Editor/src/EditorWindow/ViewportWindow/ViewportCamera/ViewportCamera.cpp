#include "PCH/PCH.h"

#include "ViewportCamera.h"

VL::Ref<VL::Framebuffer> ViewportCamera::GetSceneFramebuffer()
{
	return this->m_SceneFramebuffer;
}

VL::Ref<VL::Framebuffer> ViewportCamera::GetEditorFramebuffer()
{
	return this->m_EditorFramebuffer;
}

void ViewportCamera::Update(VL::Input& input, float timeStep, bool isInWindow)
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

void ViewportCamera::Render(VL::Ref<VL::GameState> gameState, ImVec2 viewportSize)
{
	auto spec = this->m_SceneFramebuffer->GetSpec();
	if (viewportSize.x != spec.Width || viewportSize.y != spec.Height)
	{
		spec.Width = std::clamp((uint32_t)viewportSize.x, (uint32_t)1, (uint32_t)8000);
		spec.Height = std::clamp((uint32_t)viewportSize.y, (uint32_t)1, (uint32_t)8000);

		this->m_SceneFramebuffer->SetSpec(spec);
		this->m_EditorFramebuffer->SetSpec(spec);
		this->m_EntityPickFramebuffer->SetSpec(spec);
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

	this->m_Renderer->Begin(this->m_SceneFramebuffer);
	this->m_Renderer->Submit(gameState);
	this->m_Renderer->Submit(editorEye);
	this->m_Renderer->End();

	/*this->m_Renderer->Begin(this->m_EntityPickFramebuffer);
	for (auto& entity : *gameState)
	{
		auto transform = gameState->GetComponent<VL::Transform>(entity.entity, 0);
		VL::Mat4x4 modelMatrix = transform->GetModelMatrix();

		for (auto& component : entity)
		{
			if (component.Is<VL::MeshRenderer>())
			{
				auto meshRenderer = component.As<VL::MeshRenderer>();

				VL::RendererModel model;
				model.LayerMask = meshRenderer->GetLayerMask();
				model.material = meshRenderer->GetMaterial();
				model.mesh = meshRenderer->GetMesh();
				model.ModelMatrix = modelMatrix;

				this->m_Renderer->Submit(model);
			}
		}
	}
	editorEye.Target = nullptr;
	this->m_Renderer->Submit(editorEye);
	this->m_Renderer->End();*/
}

void ViewportCamera::Invalidate()
{
	this->m_EditorFramebuffer->Invalidate();
	this->m_SceneFramebuffer->Invalidate();
	this->m_EntityPickFramebuffer->Invalidate();
}

ViewportCamera::ViewportCamera()
{
	VL::FramebufferSpec spec;
	spec.ColorAttachments = { VL::TextureSpec(VL::TextureFormat::RGBA16F) };
	spec.DepthAttachment = VL::TextureSpec(VL::TextureFormat::Depth24Stencil8);
	spec.Height = 1080;
	spec.Width = 1920;

	this->m_SceneFramebuffer = VL::Framebuffer::Create(spec);
	this->m_EditorFramebuffer = VL::Framebuffer::Create(spec);

	VL::FramebufferSpec entityPickSpec;
	entityPickSpec.ColorAttachments = { VL::TextureSpec(VL::TextureFormat::RedInteger) };
	entityPickSpec.DepthAttachment = VL::TextureSpec(VL::TextureFormat::Depth24Stencil8);
	entityPickSpec.Height = 1080;
	entityPickSpec.Width = 1920;

	this->m_EntityPickFramebuffer = VL::Framebuffer::Create(entityPickSpec);

	this->m_Renderer = VL::ForwardRenderer::Create();

	this->m_BallCenter = VL::Vec3(0, 1, 0);
	this->m_Distance = 10.0f;

	this->m_Position = this->m_BallCenter + VL::Vec3(0.0, 0.0, 1.0) * this->m_Distance;
	this->m_Rotation = VL::Vec3(0.0, 0.0, 0.0);

	this->m_GridEffect = VL::Effect::Create(VL::Shader::Create("data/shaders/grid.shader"));
}