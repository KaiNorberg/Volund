#include "PCH/PCH.h"

#include "Editor.h"

#include "VML/VML.h"

#include "FileDialog/FileDialog.h"

#include "Widget/EntitiesWidget/EntitiesWidget.h"
#include "Widget/ViewportWidget/ViewportWidget.h"
#include "Widget/InspectorWidget/InspectorWidget.h"
#include "Widget/OutputWidget/OutputWidget.h"

#include <windows.h>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_win32.h>
#include <ImGuizmo.h>

#include "ImGuiStyle.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

VL::Ref<Project> Editor::GetProject()
{
	return this->_Project;
}

VL::Ref<VL::Window> Editor::GetWindow()
{
	return this->_Window;
}

void Editor::OnRun()
{
	static std::string IniFilename = std::filesystem::current_path().string() + "\\imgui.ini";

	VL::RenderingAPI::Select(VL::GraphicsAPI::OPENGL);

	this->_Window = VL::Ref<VL::Window>(new VL::Window(this->GetEventDispatcher(), 1980, 1080, false));

	this->_Window->SetTitle("Volund Editor");
	this->_Window->SetCursorMode(VL::CursorMode::NORMAL);
	this->_Window->SetFocus();

	this->_Context = VL::Context::Create(this->_Window);
	this->_Context->SetVSync(true);
	this->_Context->MakeCurrent();

	VL::RenderingAPI::Init();
	VL::Renderer::Init(new VL::ForwardRenderer());

	this->_Project = VL::Ref<Project>(new Project());

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.Fonts->AddFontFromFileTTF("data/Fonts/OpenSans-Regular.ttf", 18.0f);
	io.IniFilename = IniFilename.c_str();

	SetupImGuiStyle();

	this->_Window->SetProcedureCatch((VL::ProcCatch)ImGui_ImplWin32_WndProcHandler);

	ImGui_ImplWin32_Init(this->_Window->GetHandle());
	ImGui_ImplOpenGL3_Init();

	this->_WidgetContainer.PushBack(new EntitiesWidget(this, true));
	this->_WidgetContainer.PushBack(new ViewportWidget(this, true));
	this->_WidgetContainer.PushBack(new InspectorWidget(this, true));
	this->_WidgetContainer.PushBack(new OutputWidget(this, true));

	this->_Window->Show();
}

void Editor::OnTerminate()
{

}

void Editor::OnUpdate(VL::TimeStep TS)
{
	this->_Context->MakeCurrent();

	this->Draw(TS);

	this->_Context->Flush();
	VL::RenderingAPI::Clear();
	this->_Window->Update();
}

void Editor::OnEvent(VL::Event* E)
{
	this->_Input.HandleEvent(E);

	this->HandleShortcuts();

	for (const auto& View : this->_WidgetContainer)
	{
		for (const auto& Widget : View)
		{
			if (Widget->_IsActive)
			{
				Widget->OnEvent(E);
			}
		}
	}

	switch (E->GetType())
	{
	case VL::EventType::WINDOW_CLOSE:
	{
		this->Terminate();
	}
	break;
	}
}

void Editor::Draw(VL::TimeStep TS)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGuizmo::BeginFrame();

	if (this->BeginDockSpace())
	{
		this->DrawMenuBar();

		for (const auto& View : this->_WidgetContainer)
		{
			for (const auto& Widget : View)
			{
				if (Widget->_IsActive)
				{
					Widget->Draw(TS);
				}
			}
		}

	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::HandleShortcuts()
{
	if (this->_Input.IsHeld(VOLUND_KEY_CONTROL))
	{
		if (this->_Input.IsHeld(VOLUND_KEY_SHIFT))
		{
			if (this->_Input.IsPressed('N'))
			{
				//auto Editor = GetLayer<EditorLayer>();
				//Editor->LoadProject(FileDialog::OpenFile("Volund Project (*.vproj)\0*.vproj\0", this->_Window));
			}

			if (this->_Input.IsPressed('O'))
			{
				this->_Project->Load(FileDialog::OpenFile("Volund Project (*.vproj)\0*.vproj\0", this->_Window));
			}

			if (this->_Project->Loaded())
			{
				if (this->_Input.IsPressed('S'))
				{
					this->_Project->Save(this->_Project->GetVMLFilepath());
				}

				if (this->_Input.IsPressed('A'))
				{
					this->_Project->Save(FileDialog::SaveFile("Volund Project (*.vproj)\0*.vproj\0", this->_Window));
				}
			}
		}
		else if (this->_Project->Loaded())
		{
			if (this->_Input.IsPressed('N'))
			{
				//auto Editor = GetLayer<EditorLayer>();
				//Editor->LoadProject(FileDialog::OpenFile("Volund Project (*.vproj)\0*.vproj\0", this->_Window));
			}

			if (this->_Input.IsPressed('O'))
			{
				this->_Project->LoadScene(FileDialog::OpenFile("Volund Scene (*.vscene)\0*.vscene\0", this->_Window));
			}

			if (this->_Input.IsPressed('S'))
			{
				this->_Project->SaveScene(this->_Project->GetSceneFilepath());
			}

			if (this->_Input.IsPressed('A'))
			{
				this->_Project->SaveScene(FileDialog::OpenFile("Volund Scene (*.vscene)\0*.vscene\0", this->_Window));
			}
		}
	}
}

bool Editor::BeginDockSpace()
{
	static bool Open = true;

	static ImGuiDockNodeFlags DockspaceFlags;
	static ImGuiWindowFlags WindowFlags =
		ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	const ImGuiViewport* ViewPort = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ViewPort->WorkPos);
	ImGui::SetNextWindowSize(ViewPort->WorkSize);
	ImGui::SetNextWindowViewport(ViewPort->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	if (ImGui::Begin("DockSpace Demo", &Open, WindowFlags))
	{
		ImGui::PopStyleVar(3);

		ImGuiID DockspaceID = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(DockspaceID, ImVec2(0.0f, 0.0f), DockspaceFlags);
	
		return true;
	}
	else
	{
		ImGui::PopStyleVar(3);

		return false;
	}
}

void Editor::DrawMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			this->DrawProjectMenu();

			this->DrawSceneMenu();

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Widgets"))
		{
			for (const auto& View : this->_WidgetContainer)
			{
				for (const auto& Widget : View)
				{
					if (ImGui::MenuItem(Widget->GetName()))
					{
						Widget->_IsActive = true;
					}
				}
			}

			ImGui::EndMenu();
		}

		auto Project = this->_Project;

		if (Project != nullptr)
		{
			std::string ProjectName = std::filesystem::path(Project->GetVMLFilepath()).filename().string();
			std::string SceneName = std::filesystem::path(Project->GetSceneFilepath()).filename().string();
			ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize(ProjectName.c_str()).x - ImGui::CalcTextSize(SceneName.c_str()).x - 50);
			ImGui::Text("%s | %s", ProjectName.c_str(), SceneName.c_str());
		}

		ImGui::EndMenuBar();
	}
}

void Editor::DrawProjectMenu()
{
	if (ImGui::BeginMenu("Project"))
	{
		if (ImGui::MenuItem("New", "Ctrl+Shift+N"))
		{
			//auto Editor = GetLayer<EditorLayer>();
			//Editor->LoadProject(FileDialog::OpenFile("Volund Project (*.vproj)\0*.vproj\0", this->_Window));
		}

		if (ImGui::MenuItem("Open", "Ctrl+Shift+O"))
		{
			this->_Project->Load(FileDialog::OpenFile("Volund Project (*.vproj)\0*.vproj\0", this->_Window));
		}

		if (this->_Project->Loaded())
		{
			if (ImGui::MenuItem("Save", "Ctrl+Shift+S"))
			{
				this->_Project->Save(this->_Project->GetVMLFilepath());
			}

			if (ImGui::MenuItem("Save As", "Ctrl+Shift+A"))
			{
				this->_Project->Save(FileDialog::SaveFile("Volund Project (*.vproj)\0*.vproj\0", this->_Window));
			}
		}

		ImGui::EndMenu();
	}
}

void Editor::DrawSceneMenu()
{
	if (this->_Project->Loaded())
	{
		if (ImGui::BeginMenu("Scene"))
		{
			if (ImGui::MenuItem("New", "Ctrl+N"))
			{
				//auto Editor = GetLayer<EditorLayer>();
				//Editor->LoadProject(FileDialog::OpenFile("Volund Project (*.vproj)\0*.vproj\0", this->_Window));
			}

			if (ImGui::MenuItem("Open", "Ctrl+O"))
			{
				this->_Project->LoadScene(FileDialog::OpenFile("Volund Scene (*.vscene)\0*.vscene\0", this->_Window));
			}

			if (ImGui::MenuItem("Save", "Ctrl+S"))
			{
				this->_Project->SaveScene(this->_Project->GetSceneFilepath());
			}

			if (ImGui::MenuItem("Save As", "Ctrl+A"))
			{
				this->_Project->SaveScene(FileDialog::OpenFile("Volund Scene (*.vscene)\0*.vscene\0", this->_Window));
			}

			ImGui::EndMenu();
		}
	}
}