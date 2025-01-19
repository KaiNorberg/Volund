#include "Editor.h"
#include "ImGuiStyles.h"
#include "EditorContext.h"

#include "Panel/Output.h"
#include "Panel/Viewport.h"
#include "Panel/Inspector.h"
#include "Panel/Hierarchy.h"
#include "Panel/Explorer.h"
#include "Panel/MaterialEditor.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <imgui_internal.h>
#include <memory>
#include <misc/cpp/imgui_stdlib.h>

void Editor::Procedure(const VL::Event& e)
{
	auto scene = this->m_context->state->SceneRef();

	this->m_input.Procedure(e);

	if (this->m_context->IsPaused())
	{
		if (e.type == VOLUND_EVENT_RENDER)
		{
			scene->Procedure(e);
		}
	}
	else
	{
		scene->Procedure(e);
	}

	if (e.type != VOLUND_EVENT_RENDER)
	{
    	for (auto& panel : this->m_panels)
    	{
            panel->Procedure(e);
    	}
	}

	switch (e.type)
	{
	case VOLUND_EVENT_RENDER:
	{
	    ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

		if (this->BeginDockSpace())
		{
			this->DrawBackground();

			for (auto& panel : this->m_panels)
			{
			    panel->Procedure(e);
			}
		}

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	break;
	case VOLUND_EVENT_KEY:
	{
		if (this->m_input.IsHeld(VOLUND_KEY_CONTROL))
		{
			if (this->m_input.IsPressed('R'))
			{
				this->GetDispatcher()->Enqueue(EDITOR_CMD_RELOAD_SCENE);
			}
			else if (this->m_input.IsPressed('E'))
			{
				this->GetDispatcher()->Enqueue(EDITOR_CMD_LOAD_SCENE);
			}
			else if (this->m_input.IsPressed('N'))
			{
				this->GetDispatcher()->Enqueue(EDITOR_CMD_NEW_SCENE);
			}
			else if (this->m_input.IsPressed('S'))
			{
				this->GetDispatcher()->Enqueue(EDITOR_CMD_SAVE_SCENE);
			}
		}
	}
	break;
	case VOLUND_EVENT_CLOSE:
	{
		this->Terminate();
	}
	break;
	case EDITOR_CMD_RELOAD_SCENE:
	{
		//scene->ReloadScene();
		this->GetDispatcher()->Enqueue(EDITOR_EVENT_RESET);
	}
	break;
	case EDITOR_CMD_LOAD_SCENE:
	{
		//const std::string filepath = VL::Dialog::OpenFile(this->GetWindow());
		const std::string filepath = "/home/kai/Documents/GitHub/Volund/examples/Simple/simple.scene.lua";
		if (this->m_context->state->LoadScene(filepath) != nullptr)
		{
			this->GetDispatcher()->Enqueue(EDITOR_EVENT_RESET);
		}
	}
	break;
	case EDITOR_CMD_SAVE_SCENE:
	{
		this->m_context->state->SaveScene(".");
	}
	break;
	case EDITOR_CMD_NEW_SCENE:
	{
		/*const std::string filepath = VL::Dialog::OpenFolder(this->GetWindow());

		if (!filepath.empty())
		{
			VL::Serializer serializer(VOLUND_SERIAL_FILE_TYPE_SCENE);
			serializer.WriteToFile(filepath + "/scene.lua");

			scene->LoadScene(filepath + "/scene.lua");
		}*/
		this->GetDispatcher()->Enqueue(EDITOR_EVENT_RESET);
	}
	break;
	case EDITOR_CMD_PLAY:
	{
		if (scene == nullptr || !this->m_context->m_paused)
		{
			return;
		}

		//scene->SaveScene();
		//scene->ReloadScene();

		SetDarkImGuiStyle();

		this->m_context->m_paused = false;
	}
	break;
	case EDITOR_CMD_PAUSE:
	{
		if (scene == nullptr || this->m_context->m_paused)
		{
			return;
		}

		this->m_context->m_paused = true;

		//scene->ReloadScene();

		SetDefaultImGuiStyle();
	}
	break;
	default:
	{

	}
	break;
	}
}

Editor::Editor()
{
	auto window = this->GetWindow();
	window->SetIcon("data/icons/logo.png");
	window->SetTitle("Volund Editor");

	VL::RenderingAPI::Init(VL::GraphicsAPI::OpenGL);

	//this->AttachModule<VL::AudioModule>();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.IniFilename = "data/imgui.ini";
	io.Fonts->AddFontFromFileTTF("data/fonts/OpenSans-Regular.ttf", 18.0f);

	ImGui_ImplGlfw_InitForOpenGL(window->GetGlfwWindow(), false);
	ImGui_ImplOpenGL3_Init();

	window->ConnectWindowFocusCallback(ImGui_ImplGlfw_WindowFocusCallback);
	window->ConnectCursorEnterCallback(ImGui_ImplGlfw_CursorEnterCallback);
	window->ConnectCursorPositionCallback(ImGui_ImplGlfw_CursorPosCallback);
	window->ConnectMouseButtonCallback(ImGui_ImplGlfw_MouseButtonCallback);
	window->ConnectScrollCallback(ImGui_ImplGlfw_ScrollCallback);
	window->ConnectKeyCallback(ImGui_ImplGlfw_KeyCallback);
	window->ConnectCharCallback(ImGui_ImplGlfw_CharCallback);

	this->m_context = std::make_shared<EditorContext>(this->GetDispatcher());

	this->m_panels.push_back(std::make_shared<Viewport>(this->m_context));
	this->m_panels.push_back(std::make_shared<Output>(this->m_context));
	this->m_panels.push_back(std::make_shared<Inspector>(this->m_context));
	this->m_panels.push_back(std::make_shared<Explorer>(this->m_context));
	this->m_panels.push_back(std::make_shared<Hierarchy>(this->m_context));
	this->m_panels.push_back(std::make_shared<MaterialEditor>(this->m_context));

	SetDefaultImGuiStyle();

	ImGui::LoadIniSettingsFromDisk("data/imgui.ini");
}

bool Editor::BeginDockSpace()
{
	static bool open = true;

	static ImGuiDockNodeFlags dockspaceFlags;
	static ImGuiWindowFlags windowFlags =
		ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	const ImGuiViewport* viewPort = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewPort->WorkPos);
	ImGui::SetNextWindowSize(viewPort->WorkSize);
	ImGui::SetNextWindowViewport(viewPort->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	if (ImGui::Begin("DockSpace", &open, windowFlags))
	{
		ImGui::PopStyleVar(3);

		const ImGuiID dockspaceId = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);

		return true;
	}
	else
	{
		ImGui::PopStyleVar(3);

		return false;
	}
}

void Editor::DrawBackground()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::BeginMenu("Load"))
			{
				if (ImGui::MenuItem("Scene", "Ctrl + E"))
				{
					this->GetDispatcher()->Enqueue(EDITOR_CMD_LOAD_SCENE);
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Save"))
			{
				if (ImGui::MenuItem("Scene", "Ctrl + S"))
				{
					this->GetDispatcher()->Enqueue(EDITOR_CMD_SAVE_SCENE);
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Reload"))
			{
				if (ImGui::MenuItem("Scene", "Ctrl + R"))
				{
					this->GetDispatcher()->Enqueue(EDITOR_CMD_RELOAD_SCENE);
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
