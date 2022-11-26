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

	if (this->_Input.IsHeld(VOLUND_KEY_SHIFT))
	{
		if (this->_Input.IsPressed('R'))
		{
			this->_SelectedScene = VL::Ref<VL::Scene>(new VL::Scene(this->_SelectedScene->GetFilepath()));
		}
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
			ImGui::SameLine();

			if (ImGui::Button("Reload (Shift + R)"))
			{
				this->_SelectedScene = VL::Ref<VL::Scene>(new VL::Scene(this->_SelectedScene->GetFilepath()));
			}
		}

		if (this->_SelectedScene != nullptr)
		{
			if (ImGui::BeginChild("ViewPort"))
			{
				this->_Framebuffer->Bind();

				auto ViewportSize = ImGui::GetContentRegionAvail();

				VL::RenderingAPI::Clear();
				VL::RenderingAPI::SetViewPort(0, 0, ViewportSize.x, ViewportSize.y);

				this->_SelectedScene->OnUpdate(TS);

				float XRatio = ViewportSize.x / this->_Framebuffer->GetSpec().Width;
				float YRatio = ViewportSize.y / this->_Framebuffer->GetSpec().Height;

				ImGui::Image(reinterpret_cast<void*>(this->_Framebuffer->GetAttachment(0)), ViewportSize, ImVec2(0, 1 * YRatio), ImVec2(1 * XRatio, 0));

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
	Spec.Height = 2160;
	Spec.Width = 3840;
	Spec.ColorAttachments = { VL::TextureFormat::RGBA8 };
	Spec.DepthAttachment = VL::TextureFormat::DEPTH24STENCIL8;
	this->_Framebuffer = VL::Framebuffer::Create(Spec);
}
