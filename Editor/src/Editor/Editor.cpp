#include "PCH/PCH.h"

#include "Editor.h"

#include "EditorWindow/OutputWindow/OutputWindow.h"
#include "EditorWindow/ViewportWindow/ViewportWindow.h"
#include "EditorWindow/InspectorWindow/InspectorWindow.h"
#include "EditorWindow/HierarchyWindow/HierarchyWindow.h"
#include "EditorWindow/FilesystemWindow/FilesystemWindow.h"
#include "EditorWindow/MaterialEditor/MaterialEditor.h"

#include "EditorContext/EditorContext.h"

#include "ImGuiStyles.h"

void Editor::OnRun()
{
	VL::Ref<VL::Window> window = this->GetWindow();

	window->SetIcon("data/icons/logo.png");
	window->SetTitle("Volund Editor");

	VL::RenderingAPI::Init(VL::GraphicsAPI::OpenGL);

	auto audioModule = this->AttachModule<VL::AudioModule>();
	auto imGuiModule = this->AttachModule<VL::ImGuiModule>();
	
	this->m_Context = std::make_shared<EditorContext>(this->GetDispatcher());

	imGuiModule->SetBackgroundCallback([this]() 
	{
		this->BackgroundCallback(); 
	});

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = "data/imgui.ini";
	io.Fonts->AddFontFromFileTTF("data/fonts/OpenSans-Regular.ttf", 18.0f);

	auto viewportWindow = imGuiModule->CreateWindow<ViewportWindow>(this->m_Context);
	auto outputWindow = imGuiModule->CreateWindow<OutputWindow>(this->m_Context);
	auto inspectorWindow = imGuiModule->CreateWindow<InspectorWindow>(this->m_Context);
	auto filesystemWindow = imGuiModule->CreateWindow<FilesystemWindow>(this->m_Context);
	auto hierarchyWindow = imGuiModule->CreateWindow<HierarchyWindow>(this->m_Context);
	auto materialWindow = imGuiModule->CreateWindow<MaterialEditor>(this->m_Context);

	SetDefaultImGuiStyle();
}

void Editor::OnTerminate()
{

}

void Editor::Procedure(const VL::Event& e)
{
	this->m_Input.Procedure(e);

	if (this->m_Context->IsPaused())
	{
		if (e.Type == VOLUND_EVENT_TYPE_RENDER)
		{
			this->m_Context->GameState->Procedure(e);
		}
	}
	else
	{
		this->m_Context->GameState->Procedure(e);
	}

	switch (e.Type)
	{
	case VOLUND_EVENT_TYPE_RENDER:
	{ 	
		//auto window = context->GetWindow();
	}
	break;	
	case VOLUND_EVENT_TYPE_KEY:
	{	
		if (this->m_Input.IsHeld(VOLUND_KEY_CONTROL))
		{
			if (this->m_Input.IsPressed('R'))
			{
				this->GetDispatcher()->Enqueue(EDITOR_EVENT_TYPE_RELOAD_SCENE);
			}
			else if (this->m_Input.IsPressed('E'))
			{
				this->GetDispatcher()->Enqueue(EDITOR_EVENT_TYPE_LOAD_SCENE);
			}
			else if (this->m_Input.IsPressed('N'))
			{
				this->GetDispatcher()->Enqueue(EDITOR_EVENT_TYPE_NEW_SCENE);
			}
			else if (this->m_Input.IsPressed('S'))
			{
				this->GetDispatcher()->Enqueue(EDITOR_EVENT_TYPE_SAVE_SCENE);
			}
		}
	}
	break;
	case VOLUND_EVENT_TYPE_WINDOW_CLOSE:
	{
		this->Terminate();
	}
	break;
	case EDITOR_EVENT_TYPE_RELOAD_SCENE:
	{
		this->m_Context->GameState->ReloadScene();
		this->GetDispatcher()->Enqueue(EDITOR_EVENT_TYPE_RESET);
	}
	break;
	case EDITOR_EVENT_TYPE_LOAD_SCENE:
	{
		const std::string filepath = VL::Dialog::OpenFile(this->GetWindow());
		if (!filepath.empty())
		{
			this->m_Context->GameState->LoadScene(filepath);
		}
		this->GetDispatcher()->Enqueue(EDITOR_EVENT_TYPE_RESET);
	}
	break;
	case EDITOR_EVENT_TYPE_SAVE_SCENE:
	{
		this->m_Context->GameState->SaveScene();
	}
	break;
	case EDITOR_EVENT_TYPE_NEW_SCENE:
	{
		const std::string filepath = VL::Dialog::OpenFolder(this->GetWindow());

		if (!filepath.empty())
		{
			VL::Serializer serializer(VOLUND_SERIAL_FILE_TYPE_SCENE);
			serializer.WriteToFile(filepath + "/scene.lua");

			this->m_Context->GameState->LoadScene(filepath + "/scene.lua");
		}
		this->GetDispatcher()->Enqueue(EDITOR_EVENT_TYPE_RESET);
	}
	break;
	case EDITOR_EVENT_TYPE_PLAY:
	{
		if (this->m_Context->GameState == nullptr || !this->m_Context->m_Paused)
		{
			return;
		}

		this->m_Context->GameState->SaveScene();
		this->m_Context->GameState->ReloadScene();

		SetDarkImGuiStyle();

		this->m_Context->m_Paused = false;
	}
	break;
	case EDITOR_EVENT_TYPE_PAUSE:
	{
		if (this->m_Context->GameState == nullptr || this->m_Context->m_Paused)
		{
			return;
		}

		this->m_Context->m_Paused = true;

		this->m_Context->GameState->ReloadScene();

		SetDefaultImGuiStyle();
	}
	break;
	default:
	{

	}
	break;
	}
}

void Editor::BackgroundCallback()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::BeginMenu("Load"))
			{
				if (ImGui::MenuItem("Scene", "Ctrl + E"))
				{
					this->GetDispatcher()->Enqueue(EDITOR_EVENT_TYPE_LOAD_SCENE);
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Save"))
			{
				if (ImGui::MenuItem("Scene", "Ctrl + S"))
				{
					this->GetDispatcher()->Enqueue(EDITOR_EVENT_TYPE_SAVE_SCENE);
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Reload"))
			{
				if (ImGui::MenuItem("Scene", "Ctrl + R"))
				{
					this->GetDispatcher()->Enqueue(EDITOR_EVENT_TYPE_RELOAD_SCENE);
				}

				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{
			if (ImGui::MenuItem("Not implemented"))
			{

			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}
