#include "PCH/PCH.h"
#include "ViewportWidget.h"

#include "Editor/Editor.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

#include "Scene/Component/MeshRenderer/MeshRenderer.h"
#include "Scene/Component/PointLight/PointLight.h"

const char* ViewportWidget::GetName()
{
	return "Viewport";
}

void ViewportWidget::OnEvent(VL::Event* E)
{
	this->_Input.HandleEvent(E);
	if (this->_GameScene != nullptr)
	{
		if (this->_Input.IsHeld(VOLUND_KEY_TAB))
		{
			this->_Editor->GetWindow()->SetCursorMode(VL::CursorMode::NORMAL);
		}
		else
		{
			this->_Editor->GetWindow()->SetCursorMode(VL::CursorMode::DISABLED);
			this->_GameScene->OnEvent(E);
		}
	}
}

void ViewportWidget::Draw(VL::TimeStep TS)
{	
	this->DrawViewport(TS);
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

	if (this->_Editor->GetProject()->SceneLoaded())
	{
		if (this->_GameScene != nullptr)
		{
			Align(ImGui::CalcTextSize("Pause").x, 0.5f);
			if (ImGui::Button("Pause"))
			{
				this->_GameScene = nullptr;
			}
		}
		else
		{
			Align(ImGui::CalcTextSize("Play").x, 0.5f);
			if (ImGui::Button("Play"))
			{
				this->_GameScene = VL::Scene::Copy(this->_Editor->GetProject()->GetScene());
			}
		}

		this->_Framebuffer->Bind();
		VL::RenderingAPI::Clear();
		VL::RenderingAPI::SetViewPort(0, 0, this->_Framebuffer->GetSpec().Width, this->_Framebuffer->GetSpec().Height);

		if (this->_GameScene != nullptr)
		{
			this->DrawGameView(TS, this->_GameScene);
		}
		else
		{
			this->MoveEye(TS);
			this->DrawSceneView(TS);
		}

		this->_Framebuffer->Unbind();
		ImGui::Image(reinterpret_cast<void*>(this->_Framebuffer->GetAttachment(0)), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
	}
	else
	{
		ImGui::Text("No Scene Loaded!");
	}

	ImGui::End();
}


void ViewportWidget::DrawSceneView(VL::TimeStep TS)
{
	auto ViewportSize = ImGui::GetContentRegionAvail();

	VL::Quat EyeQuaternion = VL::Quat(VL::Math::ToRadians(this->_Eye.Rotation));
	VL::Mat4x4 ViewMatrix = glm::lookAt(this->_Eye.Position, this->_Eye.Position + EyeQuaternion * VL::Math::Back, EyeQuaternion * VL::Math::Up);
	VL::Mat4x4 ProjectionMatrix = glm::perspective(glm::radians(70.0f), (float)ViewportSize.x / (float)ViewportSize.y, 0.1f, 1000.0f);
	VL::Renderer::Begin(ViewMatrix, ProjectionMatrix);

	auto Scene = this->_Editor->GetProject()->GetScene();

	auto TransformView = Scene->View<VL::Transform>();
	auto MeshRendererView = Scene->View<VL::MeshRenderer>();
	auto PointLightView = Scene->View<VL::PointLight>();

	for (auto& View : TransformView)
	{
		for (auto& Component : View)
		{
			Component->OnUpdate(0.0f);
		}
	}

	for (auto& View : MeshRendererView)
	{
		for (auto& Component : View)
		{
			Component->OnUpdate(0.0f);
		}
	}

	for (auto& View : PointLightView)
	{
		for (auto& Component : View)
		{
			Component->OnUpdate(0.0f);
		}
	}	
	
	VL::Renderer::End();
}

void ViewportWidget::DrawGameView(VL::TimeStep TS, VL::Ref<VL::Scene> GameScene)
{
	auto ViewportSize = ImGui::GetContentRegionAvail();

	VL::RenderingAPI::Clear();
	VL::RenderingAPI::SetViewPort(0, 0, this->_Framebuffer->GetSpec().Width, this->_Framebuffer->GetSpec().Height);

	VL::Camera* ActiveCamera = VL::Camera::GetActiveCamera(GameScene);

	if (ActiveCamera != nullptr)
	{
		VL::Renderer::Begin(ActiveCamera->GetViewMatrix(), ActiveCamera->GetProjectionMatrix((float)ViewportSize.x / (float)ViewportSize.y));

		GameScene->OnUpdate(TS);

		VL::Renderer::End();
	}
	else
	{
		ImGui::Text("Scene does not contain an ActiveCamera!");
	}
}

ViewportWidget::ViewportWidget(Editor* editor, bool Active)
	: Widget(editor, Active)
{
	VL::FramebufferSpec Spec;
	Spec.Height = 1080;
	Spec.Width = 1980;
	Spec.ColorAttachments = { VL::TextureFormat::RGBA8 };
	Spec.DepthAttachment = VL::TextureFormat::DEPTH24STENCIL8;
	this->_Framebuffer = VL::Framebuffer::Create(Spec);
}