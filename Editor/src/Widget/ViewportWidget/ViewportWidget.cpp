#include "PCH/PCH.h"

#include "ViewportWidget.h"

const char* ViewportWidget::GetName()
{
	return "Viewport";
}

void ViewportWidget::OnEvent(VL::Event* E)
{
	this->_Input.HandleEvent(E);

	if (!VL::Scene::GetFilepath().empty())
	{
		VL::Scene::OnEvent(E);
	}

	if (this->_Input.IsHeld(VOLUND_KEY_SHIFT))
	{
		if (this->_Input.IsPressed('R'))
		{
			VL::Scene::Load(VL::Scene::GetFilepath());
		}		
		else if (this->_Input.IsPressed('E'))
		{
			std::string Filepath = VL::FileDialog::OpenFile();
			if (!Filepath.empty())
			{
				VL::Scene::Load(Filepath);
			}
		}
	}
}

void ViewportWidget::OnUpdate(VL::TimeStep TS)
{
	if (ImGui::Begin(this->GetName(), &this->IsActive))
	{
		if (ImGui::Button("Load Scene (Shift + E)"))
		{
			std::string Filepath = VL::FileDialog::OpenFile();
			if (!Filepath.empty())
			{
				VL::Scene::Load(Filepath);
			}
		}

		if (!VL::Scene::GetFilepath().empty())
		{
			ImGui::SameLine();

			if (ImGui::Button("Reload (Shift + R)"))
			{
				VL::Scene::Load(VL::Scene::GetFilepath());
			}

			if (ImGui::BeginChild("ViewPort"))
			{
				this->_Framebuffer->Bind();

				auto ViewportSize = ImGui::GetContentRegionAvail();

				VL::RenderingAPI::Clear();
				VL::RenderingAPI::SetViewPort(0, 0, (int32_t)ViewportSize.x, (int32_t)ViewportSize.y);

				VL::Scene::OnUpdate(TS);

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
