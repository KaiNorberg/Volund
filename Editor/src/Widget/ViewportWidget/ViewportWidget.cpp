#include "PCH/PCH.h"

#include "ViewportWidget.h"

const char* ViewportWidget::GetName()
{
	return "Viewport";
}

void ViewportWidget::OnEvent(VL::Event* E)
{
	this->_Input.HandleEvent(E);

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
				ImGui::End();
				return;
			}
		}

		if (!VL::Scene::GetFilepath().empty())
		{
			ImGui::SameLine();

			if (ImGui::Button("Reload (Shift + R)"))
			{
				VL::Scene::Load(VL::Scene::GetFilepath());
				ImGui::End();
				return;
			}

			if (ImGui::BeginChild("ViewPort"))
			{
				auto ViewportSize = ImGui::GetContentRegionAvail();

				VL::Scene::ResizeTarget(ViewportSize.x, ViewportSize.y);

				VL::Scene::Render(TS);

				ImGui::Image(reinterpret_cast<void*>(VL::Scene::GetTargetBuffer()->GetAttachment(0)), ViewportSize, ImVec2(0, 1), ImVec2(1, 0));

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

ViewportWidget::ViewportWidget()
{

}
	