#include "PCH/PCH.h"

#include "ViewportWidget.h"

const char* ViewportWidget::GetName()
{
	return "Viewport";
}

void ViewportWidget::OnKey(const VL::Event& E)
{
	auto GameModule = this->_App->GetModule<VL::GameModule>();

	this->_Input.Procedure(E);

	if (this->_Input.IsHeld(VOLUND_KEY_SHIFT))
	{
		if (this->_Input.IsPressed('R'))
		{
			auto Scene = GameModule->GetScene();
			if (Scene != nullptr)
			{
				GameModule->NewState(GameModule->GetFilepath());
			}
		}		
		else if (this->_Input.IsPressed('E'))
		{
			std::string Filepath = VL::FileDialog::OpenFile();
			if (!Filepath.empty())
			{
				GameModule->NewState(Filepath);
			}
		}
	}
}

void ViewportWidget::OnRender()
{
	auto GameModule = this->_App->GetModule<VL::GameModule>();

	if (ImGui::Begin(this->GetName(), &this->IsActive))
	{
		if (ImGui::Button("Load Scene (Shift + E)"))
		{
			std::string Filepath = VL::FileDialog::OpenFile();
			if (!Filepath.empty())
			{
				GameModule->NewState(Filepath);
				ImGui::End();
				return;
			}
		}

		auto Scene = GameModule->GetScene();
		if (Scene != nullptr)
		{
			ImGui::SameLine();

			if (ImGui::Button("Reload (Shift + R)"))
			{
				GameModule->NewState(GameModule->GetFilepath());
				ImGui::End();
				return;
			}

			if (ImGui::BeginChild("ViewPort"))
			{
				auto ViewportSize = ImGui::GetContentRegionAvail();

				Scene->ResizeTarget(ViewportSize.x, ViewportSize.y);

				ImGui::Image(reinterpret_cast<void*>(Scene->GetTargetBuffer()->GetAttachment(0)), ViewportSize, ImVec2(0, 1), ImVec2(1, 0));

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

ViewportWidget::ViewportWidget(VL::Application* App)
{
	this->_App = App;
}
	