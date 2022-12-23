#include "PCH/PCH.h"

#include "ViewportWidget.h"

const char* ViewportWidget::GetName()
{
	return "Viewport";
}

void ViewportWidget::OnKey(const VL::Event& E)
{
	auto LuaModule = this->_App->GetModule<VL::LuaModule>();

	this->_Input.HandleEvent(E);

	if (this->_Input.IsHeld(VOLUND_KEY_SHIFT))
	{
		if (this->_Input.IsPressed('R'))
		{
			auto Scene = LuaModule->GetScene();
			if (Scene != nullptr)
			{
				LuaModule->LoadScene(LuaModule->GetFilepath());
			}
		}		
		else if (this->_Input.IsPressed('E'))
		{
			std::string Filepath = VL::FileDialog::OpenFile();
			if (!Filepath.empty())
			{
				LuaModule->LoadScene(Filepath);
			}
		}
	}
}

void ViewportWidget::OnRender()
{
	auto LuaModule = this->_App->GetModule<VL::LuaModule>();

	if (ImGui::Begin(this->GetName(), &this->IsActive))
	{
		if (ImGui::Button("Load Scene (Shift + E)"))
		{
			std::string Filepath = VL::FileDialog::OpenFile();
			if (!Filepath.empty())
			{
				LuaModule->LoadScene(Filepath);
				ImGui::End();
				return;
			}
		}

		auto Scene = LuaModule->GetScene();
		if (Scene != nullptr)
		{
			ImGui::SameLine();

			if (ImGui::Button("Reload (Shift + R)"))
			{
				LuaModule->LoadScene(LuaModule->GetFilepath());
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
	