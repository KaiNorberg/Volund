#include "PCH/PCH.h"

#include "ViewportWidget.h"

const char* ViewportWidget::GetName()
{
	return "Viewport";
}

void ViewportWidget::OnKey(const VL::Event& e)
{
	const auto gameModule = this->m_App->GetModule<VL::GameModule>();
	auto window = this->m_App->GetModule<VL::WindowModule>()->GetWindow();

	this->m_Input.Procedure(e);

	//if (this->m_Input.IsHeld(VOLUND_KEY_SHIFT))
	{
		if (this->m_Input.IsPressed('R'))
		{
			const auto scene = gameModule->GetScene();
			if (scene != nullptr)
			{
				gameModule->LoadNewState(gameModule->GetFilepath());
			}
		}		
		else if (this->m_Input.IsPressed('E'))
		{
			const std::string filepath = VL::Dialog::OpenFile(window);
			if (!filepath.empty())
			{
				gameModule->LoadNewState(filepath);
			}
		}
	}
}

void ViewportWidget::OnRender()
{
	const auto gameModule = this->m_App->GetModule<VL::GameModule>();
	auto window = this->m_App->GetModule<VL::WindowModule>()->GetWindow();

	if (ImGui::Begin(this->GetName(), &this->IsActive))
	{
		if (ImGui::Button("Load Scene (Shift + E)"))
		{
			const std::string filepath = VL::Dialog::OpenFile(window);
			if (!filepath.empty())
			{
				gameModule->LoadNewState(filepath);
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
				gameModule->LoadNewState(gameModule->GetFilepath());
				ImGui::End();
				return;
			}

			if (ImGui::BeginChild("ViewPort"))
			{
				ImVec2 vMin = ImGui::GetWindowContentRegionMin();
				ImVec2 vMax = ImGui::GetWindowContentRegionMax();

				ImVec2 viewportSize = ImVec2(vMax.x - vMin.x, vMax.y - vMin.y);

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
	