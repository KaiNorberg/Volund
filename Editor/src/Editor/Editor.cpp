#include "PCH/PCH.h"

#include "Editor.h"

#include "Widget/OutputWidget/OutputWidget.h"
#include "Widget/ViewportWidget/ViewportWidget.h"
#include "Widget/InspectorWidget/InspectorWidget.h"
#include "Widget/HierarchyWidget/HierarchyWidget.h"

#include "EditorModule/EditorModule.h"

void Editor::OnRun()
{
	this->AttachModule(new VL::WindowModule(VL::GraphicsAPI::OpenGL, std::make_shared<VL::ForwardRenderer>()));
	this->AttachModule(new VL::ImGuiModule());
	this->AttachModule(new VL::AudioModule());
	this->AttachModule(new EditorModule());

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("data/fonts/OpenSans-Regular.ttf", 18.0f);

	this->m_Widgets.push_back(VL::Ref<OutputWidget>(new OutputWidget(this)));
	this->m_Widgets.push_back(VL::Ref<ViewportWidget>(new ViewportWidget(this)));
	this->m_Widgets.push_back(VL::Ref<InspectorWidget>(new InspectorWidget(this)));
	this->m_Widgets.push_back(VL::Ref<HierarchyWidget>(new HierarchyWidget(this)));
}

void Editor::OnTerminate()
{

}

void Editor::Procedure(const VL::Event& e)
{
	VOLUND_PROFILE_FUNCTION();

	this->m_Input.Procedure(e);

	switch (e.Type)
	{
	case VL::EventType::Render:
	{ 	
		const auto editorModule = this->GetModule<EditorModule>();
		auto window = this->GetModule<VL::WindowModule>()->GetWindow();

		VL::ImGuiModule::BeginFrame();

		if (VL::ImGuiModule::BeginDockSpace())
		{
			//TODO: Improve readability of menu bar code
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::BeginMenu("Load"))
					{
						if (ImGui::MenuItem("Scene", "Ctrl + E"))
						{
							const std::string filepath = VL::Dialog::OpenFile(window);
							if (!filepath.empty())
							{
								editorModule->LoadNewScene(filepath);
							}
						}

						ImGui::EndMenu();
					}

					if (ImGui::BeginMenu("Save"))
					{
						if (ImGui::MenuItem("Scene", "Ctrl + S"))
						{
							editorModule->SaveScene(editorModule->GetSceneFilepath());
						}

						ImGui::EndMenu();
					}

					if (ImGui::BeginMenu("Save As"))
					{
						if (ImGui::MenuItem("Scene"))
						{
							const std::string filepath = VL::Dialog::OpenFile(window);
							if (!filepath.empty())
							{
								editorModule->SaveScene(filepath);
							}
						}

						ImGui::EndMenu();
					}

					if (ImGui::BeginMenu("Reload"))
					{
						if (ImGui::MenuItem("Scene", "Ctrl + R"))
						{
							editorModule->LoadNewScene(editorModule->GetSceneFilepath());
						}

						ImGui::EndMenu();
					}

					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Widget"))
				{
					for (const auto& widget : this->m_Widgets)
					{
						if (ImGui::MenuItem(widget->GetName()))
						{
							widget->IsActive = true;
						}
					}

					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			for (const auto& widget : this->m_Widgets)
			{
				if (widget->IsActive)
				{
					widget->Procedure(e);
				}
			}
		}

		ImGui::End();

		VL::ImGuiModule::EndFrame();

		return;
	}
	break;	
	case VL::EventType::Key:
	{	
		const auto editorModule = this->GetModule<EditorModule>();
		auto window = this->GetModule<VL::WindowModule>()->GetWindow();

		if (this->m_Input.IsHeld(VOLUND_KEY_CONTROL))
		{
			if (this->m_Input.IsPressed('R'))
			{
				const auto scene = editorModule->GetScene();
				if (scene != nullptr)
				{
					editorModule->LoadNewScene(editorModule->GetSceneFilepath());
				}
			}
			else if (this->m_Input.IsPressed('E'))
			{
				const std::string filepath = VL::Dialog::OpenFile(window);
				if (!filepath.empty())
				{
					editorModule->LoadNewScene(filepath);
				}
			}
			else if (this->m_Input.IsPressed('S'))
			{
				editorModule->SaveScene(editorModule->GetSceneFilepath());
			}
		}
	}
	break;
	case VL::EventType::WindowClose:
	{
		this->Terminate();
	}
	break;
	default:
	{

	}
	break;
	}

	for (const auto& widget : this->m_Widgets)
	{
		if (widget->IsActive)
		{
			widget->Procedure(e);
		}
	}
}