#include "PCH/PCH.h"

#include "ViewportWidget.h"

#include "Editor/EditorModule/EditorModule.h"

const char* ViewportWidget::GetName()
{
	return "Viewport";
}

void ViewportWidget::OnKey(const VL::Event& e)
{

}

void ViewportWidget::OnRender()
{
	const auto editorModule = this->m_App->GetModule<EditorModule>();
	auto window = this->m_App->GetModule<VL::WindowModule>()->GetWindow();

	if (ImGui::Begin(this->GetName(), &this->IsActive))
	{
		auto scene = editorModule->GetScene();
		if (scene != nullptr)
		{
			ImGui::SameLine();

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
	