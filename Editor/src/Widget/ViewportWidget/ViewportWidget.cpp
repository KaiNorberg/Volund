#include "PCH/PCH.h"

#include "ViewportWidget.h"

const char* ViewportWidget::GetName()
{
	return "Viewport";
}

void ViewportWidget::OnEvent(VL::Event* E)
{
	this->_Input.HandleEvent(E);

	if (this->_SelectedScene != nullptr)
	{
		this->_SelectedScene->OnEvent(E);
	}
}

void ViewportWidget::OnUpdate(VL::TimeStep TS)
{
	if (ImGui::Begin(this->GetName(), &this->IsActive))
	{
		if (ImGui::Button("Load Scene"))
		{
			std::string Filepath = VL::FileDialog::OpenFile();
			if (!Filepath.empty())
			{
				this->_SelectedScene = VL::Ref<VL::Scene>(new VL::Scene(Filepath));
			}
		}

		if (this->_SelectedScene != nullptr)
		{
			if (ImGui::BeginChild("ViewPort"))
			{
				this->_Framebuffer->Bind();
				VL::RenderingAPI::Clear(VL::RGBA(0.0f, 0.0f, 0.0f, 1.0f));
				VL::RenderingAPI::SetViewPort(0, 0, this->_Framebuffer->GetSpec().Width, this->_Framebuffer->GetSpec().Height);

				auto ViewportSize = ImGui::GetContentRegionAvail();

				VL::RenderingAPI::Clear();
				VL::RenderingAPI::SetViewPort(0, 0, this->_Framebuffer->GetSpec().Width, this->_Framebuffer->GetSpec().Height);

				VL::Camera* ActiveCamera = VL::Camera::GetActiveCamera(this->_SelectedScene);

				if (ActiveCamera != nullptr)
				{
					VL::Renderer::Begin(ActiveCamera->GetViewMatrix(), ActiveCamera->GetProjectionMatrix((float)ViewportSize.x / (float)ViewportSize.y));

					this->_SelectedScene->OnUpdate(TS);

					VL::Renderer::End();
				}
				else
				{
					ImGui::Text("Scene does not contain an ActiveCamera!");
				}

				ImGui::Image(reinterpret_cast<void*>(this->_Framebuffer->GetAttachment(0)), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));

				ImGui::EndChild();

				this->_Framebuffer->Unbind();
			}
		}
		else
		{
			ImGui::Text("No Scene Selected!");
		}

	}
	ImGui::End();
}

ViewportWidget::ViewportWidget()
{
	auto Spec = VL::FramebufferSpec();
	Spec.Height = 1080;
	Spec.Width = 1980;
	Spec.ColorAttachments = { VL::TextureFormat::RGBA8 };
	Spec.DepthAttachment = VL::TextureFormat::DEPTH24STENCIL8;
	this->_Framebuffer = VL::Framebuffer::Create(Spec);
}
