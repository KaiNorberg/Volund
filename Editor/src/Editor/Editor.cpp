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

	VL::RenderingAPI::Init(VL::GraphicsAPI::OpenGL);
	VL::Renderer::Init(std::make_shared<VL::ForwardRenderer>());

	auto window = this->GetModule<VL::WindowModule>()->GetWindow();
	this->m_Context = std::make_shared<EditorContext>(window);

	auto outputWindow = VL::Ref<OutputWindow>(new OutputWindow(this->m_Context));
	outputWindow->SetSize(VL::Vec2(1980, 300));
	outputWindow->SetPosition(VL::Vec2(0, 1080 - outputWindow->GetSize().y));
	this->GetModule<VL::ImGuiModule>()->AddWindow(outputWindow);

	auto viewportWindow = VL::Ref<ViewportWindow>(new ViewportWindow(this->m_Context));
	viewportWindow->SetSize(VL::Vec2(1980 - 800, outputWindow->GetPosition().y - 25));
	viewportWindow->SetPosition(VL::Vec2(400, 25));
	this->GetModule<VL::ImGuiModule>()->AddWindow(viewportWindow);

	auto inspectorWindow = VL::Ref<InspectorWindow>(new InspectorWindow(this->m_Context));
	inspectorWindow->SetSize(VL::Vec2(500, outputWindow->GetPosition().y - 25));
	inspectorWindow->SetPosition(VL::Vec2(viewportWindow->GetPosition().x + viewportWindow->GetSize().x, 25));
	this->GetModule<VL::ImGuiModule>()->AddWindow(inspectorWindow);

	auto hierarchyWindow = VL::Ref<HierarchyWindow>(new HierarchyWindow(this->m_Context));
	hierarchyWindow->SetSize(VL::Vec2(500, outputWindow->GetPosition().y - 25));
	hierarchyWindow->SetPosition(VL::Vec2(0, 25));
	this->GetModule<VL::ImGuiModule>()->AddWindow(hierarchyWindow);

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("data/fonts/OpenSans-Regular.ttf", 18.0f);
}

void Editor::OnTerminate()
{

}

void Editor::Procedure(const VL::Event& e)
{
	VOLUND_PROFILE_FUNCTION();

	if (this->m_Context->m_State != nullptr)
	{
		this->m_Context->m_State->Procedure(e);
	}

	this->m_Input.Procedure(e);

	switch (e.Type)
	{
	case VL::EventType::Render:
	{ 	
		auto window = this->m_Context->GetWindow();

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
		auto window = this->m_Context->GetWindow();

		if (this->m_Input.IsHeld(VOLUND_KEY_CONTROL))
		{
			if (this->m_Input.IsPressed('R'))
			{
				const auto scene = this->m_Context->GetScene();
				if (scene != nullptr)
				{
					this->m_Context->LoadNewScene(this->m_Context->GetSceneFilepath());
				}
			}
			else if (this->m_Input.IsPressed('E'))
			{
				const std::string filepath = VL::Dialog::OpenFile(window);
				if (!filepath.empty())
				{
					this->m_Context->LoadNewScene(filepath);
				}
			}
			else if (this->m_Input.IsPressed('S'))
			{
				this->m_Context->SaveScene(this->m_Context->GetSceneFilepath());
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
}