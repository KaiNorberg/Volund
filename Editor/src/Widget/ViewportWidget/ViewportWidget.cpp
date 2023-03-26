#include "PCH/PCH.h"

#include "ViewportWidget.h"

const char* ViewportWidget::GetName()
{
	return "Viewport";
}

void ViewportWidget::OnKey(const VL::Event& e)
{
	const auto gameModule = this->m_App->GetModule<VL::GameModule>();

	this->m_Input.Procedure(e);

	if (this->m_Input.IsHeld(VOLUND_KEY_SHIFT))
	{
		if (this->m_Input.IsPressed('R'))
		{
			const auto scene = gameModule->GetScene();
			if (scene != nullptr)
			{
				gameModule->NewState(gameModule->GetFilepath());
			}
		}		
		else if (this->m_Input.IsPressed('E'))
		{
			const std::string filepath = VL::FileDialog::OpenFile();
			if (!filepath.empty())
			{
				gameModule->NewState(filepath);
			}
		}
	}
}

void ViewportWidget::OnRender()
{
	const auto gameModule = this->m_App->GetModule<VL::GameModule>();

	if (ImGui::Begin(this->GetName(), &this->IsActive))
	{
		if (ImGui::Button("Load Scene (Shift + E)"))
		{
			const std::string filepath = VL::FileDialog::OpenFile();
			if (!filepath.empty())
			{
				gameModule->NewState(filepath);
				ImGui::End();
				return;
			}
		}

		auto scene = gameModule->GetScene();
		if (scene != nullptr)
		{
			ImGui::SameLine();

			if (ImGui::Button("Reload (Shift + R)"))
			{
				gameModule->NewState(gameModule->GetFilepath());
				ImGui::End();
				return;
			}

			if (ImGui::BeginChild("ViewPort"))
			{
				const auto viewportSize = ImGui::GetContentRegionAvail();

				scene->ResizeTarget(viewportSize.x, viewportSize.y);

				ImGui::Image(reinterpret_cast<void*>(scene->GetTargetBuffer()->GetAttachment(0)), viewportSize, ImVec2(0, 1), ImVec2(1, 0));

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

ViewportWidget::ViewportWidget(VL::Application* app)
{
	this->m_App = app;
}
	