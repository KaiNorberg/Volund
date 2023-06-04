#include "PCH/PCH.h"

#include "Editor.h"

#include "EditorWindow/OutputWindow/OutputWindow.h"
#include "EditorWindow/ViewportWindow/ViewportWindow.h"
#include "EditorWindow/InspectorWindow/InspectorWindow.h"
#include "EditorWindow/HierarchyWindow/HierarchyWindow.h"

#include "EditorContext/EditorContext.h"

void Editor::OnRun()
{
	this->AttachModule(new VL::WindowModule());
	this->AttachModule(new VL::AudioModule());
	this->AttachModule(new VL::ImGuiModule());
	this->AttachModule(new EditorContext());

	VL::RenderingAPI::Init(VL::GraphicsAPI::OpenGL);

	auto context = this->GetModule<EditorContext>();

	auto outputWindow = VL::Ref<OutputWindow>(new OutputWindow(context));
	outputWindow->SetSize(VL::Vec2(1980, 300));
	outputWindow->SetPosition(VL::Vec2(0, 1080 - outputWindow->GetSize().y));
	this->GetModule<VL::ImGuiModule>()->AddWindow(outputWindow);

	auto viewportWindow = VL::Ref<ViewportWindow>(new ViewportWindow(context));
	viewportWindow->SetSize(VL::Vec2(1980 - 800, outputWindow->GetPosition().y - 25));
	viewportWindow->SetPosition(VL::Vec2(400, 25));
	this->GetModule<VL::ImGuiModule>()->AddWindow(viewportWindow);

	auto inspectorWindow = VL::Ref<InspectorWindow>(new InspectorWindow(context));
	inspectorWindow->SetSize(VL::Vec2(500, outputWindow->GetPosition().y - 25));
	inspectorWindow->SetPosition(VL::Vec2(viewportWindow->GetPosition().x + viewportWindow->GetSize().x, 25));
	this->GetModule<VL::ImGuiModule>()->AddWindow(inspectorWindow);

	auto hierarchyWindow = VL::Ref<HierarchyWindow>(new HierarchyWindow(context));
	hierarchyWindow->SetSize(VL::Vec2(500, outputWindow->GetPosition().y - 25));
	hierarchyWindow->SetPosition(VL::Vec2(0, 25));
	this->GetModule<VL::ImGuiModule>()->AddWindow(hierarchyWindow);

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("data/fonts/OpenSans-Regular.ttf", 18.0f);

	std::filesystem::create_directory(EDITOR_TEMP_FOLDER);
}

void Editor::OnTerminate()
{

}

void Editor::Procedure(const VL::Event& e)
{
	VOLUND_PROFILE_FUNCTION();

	auto context = this->GetModule<EditorContext>();

	this->m_Input.Procedure(e);

	switch (e.Type)
	{
	case VL::EventType::Render:
	{ 	
		auto window = context->GetWindow();

		if (!this->m_iniLoaded)
		{
			ImGui::LoadIniSettingsFromDisk("imgui.ini");
			this->m_iniLoaded = true;
		}

		/*VL::ImGuiModule::BeginFrame();

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
								this->m_Context->LoadNewScene(filepath);
							}
						}

						ImGui::EndMenu();
					}

					if (ImGui::BeginMenu("Save"))
					{
						if (ImGui::MenuItem("Scene", "Ctrl + S"))
						{
							this->m_Context->SaveScene(this->m_Context->GetSceneFilepath());
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
								this->m_Context->SaveScene(filepath);
							}
						}

						ImGui::EndMenu();
					}

					if (ImGui::BeginMenu("Reload"))
					{
						if (ImGui::MenuItem("Scene", "Ctrl + R"))
						{
							this->m_Context->LoadNewScene(this->m_Context->GetSceneFilepath());
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

		VL::ImGuiModule::EndFrame();*/

		return;
	}
	break;	
	case VL::EventType::Key:
	{	
		auto window = context->GetWindow();

		if (this->m_Input.IsHeld(VOLUND_KEY_CONTROL))
		{
			if (this->m_Input.IsPressed('R'))
			{
				const auto scene = context->GetScene();
				if (scene != nullptr)
				{
					context->LoadScene(context->GetFilepath());
				}
			}
			else if (this->m_Input.IsPressed('E'))
			{
				const std::string filepath = VL::Dialog::OpenFile(window);
				if (!filepath.empty())
				{
					context->LoadScene(filepath);
				}
			}
			else if (this->m_Input.IsPressed('S'))
			{
				context->SaveScene(context->GetFilepath());
			}
		}
	}
	break;
	case VL::EventType::WindowClose:
	{
		std::filesystem::remove_all(EDITOR_TEMP_FOLDER);
		this->Terminate();
	}
	break;
	default:
	{

	}
	break;
	}
}