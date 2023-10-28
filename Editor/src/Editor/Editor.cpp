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
	this->m_Window->SetIcon("data/icons/logo.png");
	this->m_Window->SetTitle("Volund Editor");

	VL::RenderingAPI::Init(VL::GraphicsAPI::OpenGL);

	auto audioModule = this->AttachModule<VL::AudioModule>();
	auto imGuiModule = this->AttachModule<VL::ImGuiModule>();
	auto context = this->AttachModule<EditorContext>();
	
	imGuiModule->SetBackgroundCallback([this]() 
	{
		this->BackgroundCallback(); 
	});

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = "data/imgui.ini";
	io.Fonts->AddFontFromFileTTF("data/fonts/OpenSans-Regular.ttf", 18.0f);

	auto viewportWindow = imGuiModule->CreateWindow<ViewportWindow>(context);
	auto outputWindow = imGuiModule->CreateWindow<OutputWindow>(context);
	auto inspectorWindow = imGuiModule->CreateWindow<InspectorWindow>(context);
	auto filesystemWindow = imGuiModule->CreateWindow<FilesystemWindow>(context);
	auto hierarchyWindow = imGuiModule->CreateWindow<HierarchyWindow>(context);
	auto materialWindow = imGuiModule->CreateWindow<MaterialEditor>(context);
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
	}
	break;	
	case VOLUND_EVENT_TYPE_KEY:
	{	
		auto window = context->GetWindow();

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
