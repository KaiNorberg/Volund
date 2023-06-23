#include "PCH/PCH.h"

#include "Editor.h"

#include "EditorWindow/OutputWindow/OutputWindow.h"
#include "EditorWindow/ViewportWindow/ViewportWindow.h"
#include "EditorWindow/InspectorWindow/InspectorWindow.h"
#include "EditorWindow/HierarchyWindow/HierarchyWindow.h"
#include "EditorWindow/FilesystemWindow/FilesystemWindow.h"
#include "EditorWindow/MaterialEditor/MaterialEditor.h"

#include "EditorContext/EditorContext.h"

void Editor::OnRun()
{
	this->AttachModule(new VL::WindowModule());
	auto windowModule = this->GetModule<VL::WindowModule>();

	windowModule->GetWindow()->SetIcon("data/icons/logo.png");
	windowModule->GetWindow()->SetTitle("Volund Editor");
	VL::RenderingAPI::Init(VL::GraphicsAPI::OpenGL);

	this->AttachModule(new VL::AudioModule());
	this->AttachModule(new VL::ImGuiModule());
	this->AttachModule(new EditorContext());

	auto context = this->GetModule<EditorContext>();
	auto imGuiModule = this->GetModule<VL::ImGuiModule>();

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = "data/imgui.ini";
	io.Fonts->AddFontFromFileTTF("data/fonts/OpenSans-Regular.ttf", 18.0f);

	auto outputWindow = VL::Ref<OutputWindow>(new OutputWindow(context));
	imGuiModule->AddWindow(outputWindow);

	auto viewportWindow = VL::Ref<ViewportWindow>(new ViewportWindow(context));
	imGuiModule->AddWindow(viewportWindow);

	auto inspectorWindow = VL::Ref<InspectorWindow>(new InspectorWindow(context));
	imGuiModule->AddWindow(inspectorWindow);

	auto filesystemWindow = VL::Ref<FilesystemWindow>(new FilesystemWindow(context));
	imGuiModule->AddWindow(filesystemWindow);

	auto hierarchyWindow = VL::Ref<HierarchyWindow>(new HierarchyWindow(context));
	imGuiModule->AddWindow(hierarchyWindow);

	auto materialWindow = VL::Ref<MaterialEditor>(new MaterialEditor(context));
	imGuiModule->AddWindow(materialWindow);
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
	case VOLUND_EVENT_TYPE_RENDER:
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
	case VOLUND_EVENT_TYPE_KEY:
	{	
		auto window = context->GetWindow();

		if (this->m_Input.IsHeld(VOLUND_KEY_CONTROL))
		{
			if (this->m_Input.IsPressed('R'))
			{
				const auto scene = context->GetScene();
				if (scene != nullptr)
				{
					context->LoadScene(context->GetScenePath());
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
			else if (this->m_Input.IsPressed('N'))
			{
				const std::string filepath = VL::Dialog::OpenFolder(window);
				
				if (!filepath.empty())
				{
					VL::LuaSerializer serializer;
					serializer.WriteToFile(filepath + "/scene.lua");

					context->LoadScene(filepath + "/scene.lua");
				}
			}
			else if (this->m_Input.IsPressed('A'))
			{
				if (!context->GetParentPath().empty())
				{
					const std::string filepath = VL::Dialog::OpenFile(window);

					if (!filepath.empty())
					{
						fs::copy(filepath, context->GetParentPath());
					}
				}
			}
			else if (this->m_Input.IsPressed('S'))
			{
				context->SaveScene(context->GetScenePath());
			}
		}
	}
	break;
	case VOLUND_EVENT_TYPE_WINDOW_CLOSE:
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