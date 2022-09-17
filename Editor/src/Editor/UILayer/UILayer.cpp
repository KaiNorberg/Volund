 #include "PCH/PCH.h"

#include "UILayer.h"

#include "VML/VML.h"

#include "Editor/EditorLayer/EditorLayer.h"

#include <windows.h>
#include <shlobj.h>   

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_win32.h>

#include "ImGuiStyle.h"

#include "Widget/EntitiesWidget/EntitiesWidget.h"
#include "Widget/AssetsWidget/AssetsWidget.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void UILayer::OnAttach()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.Fonts->AddFontFromFileTTF("Data/Fonts/Inter-Regular.ttf", 16.0f);

	SetupImGuiStyle();
	//ImGui::StyleColorsDark();

	auto EditorWindow = GetLayer<EditorLayer>()->GetWindow();

	EditorWindow->SetProcedureCatch((Volund::ProcCatch)ImGui_ImplWin32_WndProcHandler);

	ImGui_ImplWin32_Init(EditorWindow->GetHandle());
	ImGui_ImplOpenGL3_Init();

	this->_WidgetContainer.PushBack(new EntitiesWidget(this));
	this->_WidgetContainer.PushBack(new AssetsWidget(this));
}

void UILayer::OnDetach()
{
	ImGui_ImplWin32_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}

void UILayer::OnUpdate(TimeStep TS)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	this->BeginDockSpace();
	{
		this->DrawMenuBar();

		this->DrawWidgets();
	}	
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UILayer::OnEvent(Event* E)
{

}

void UILayer::BeginDockSpace()
{
	static bool Open = true;

	static ImGuiDockNodeFlags DockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
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

	ImGui::Begin("DockSpace Demo", &Open, WindowFlags);

	ImGui::PopStyleVar(3);

	ImGuiID DockspaceID = ImGui::GetID("MyDockSpace");
	ImGui::DockSpace(DockspaceID, ImVec2(0.0f, 0.0f), DockspaceFlags);
}

void UILayer::DrawMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::BeginMenu("Open"))
			{
				if (ImGui::MenuItem("Project"))
				{
					auto Editor = this->GetApp()->GetLayer<EditorLayer>();
					Editor->LoadProject(this->OpenFileDialog());
				}

				if (GetLayer<EditorLayer>()->GetProject() != nullptr)
				{
					if (ImGui::MenuItem("Scene"))
					{
						auto Editor = this->GetApp()->GetLayer<EditorLayer>();
						Editor->LoadScene(this->OpenFileDialog());
					}
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Save"))
			{
				if (ImGui::MenuItem("Scene"))
				{
					auto Editor = this->GetApp()->GetLayer<EditorLayer>();
					Editor->SaveScene(this->OpenFileDialog());
				}

				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		if (GetLayer<EditorLayer>()->GetProject() != nullptr)
		{
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
		}

		ImGui::EndMenuBar();
	}
}

void UILayer::DrawWidgets()
{
	if (GetLayer<EditorLayer>()->GetProject() != nullptr)
	{
		for (const auto& View : this->_WidgetContainer)
		{
			for (const auto& Widget : View)
			{
				if (Widget->_IsActive)
				{
					Widget->OnUpdate();
				}
			}
		}
	}
}

std::string UILayer::OpenFileDialog()
{
	HRESULT f_SysHr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (FAILED(f_SysHr))
	{
		return std::string();
	}

	IFileOpenDialog* f_FileSystem = nullptr;
	f_SysHr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&f_FileSystem));
	if (FAILED(f_SysHr))
	{
		CoUninitialize();
		return std::string();
	}

	f_SysHr = f_FileSystem->Show(NULL);
	if (FAILED(f_SysHr))
	{
		f_FileSystem->Release();
		CoUninitialize();
		return std::string();
	}

	IShellItem* f_Files;
	f_SysHr = f_FileSystem->GetResult(&f_Files);
	if (FAILED(f_SysHr))
	{
		f_FileSystem->Release();
		CoUninitialize();
		return std::string();
	}

	PWSTR f_Path;
	f_SysHr = f_Files->GetDisplayName(SIGDN_FILESYSPATH, &f_Path);
	if (FAILED(f_SysHr))
	{
		f_Files->Release();
		f_FileSystem->Release();
		CoUninitialize();
		return std::string();
	}

	std::wstring path(f_Path);
	std::string c(path.begin(), path.end());

	CoTaskMemFree(f_Path);
	f_Files->Release();
	f_FileSystem->Release();
	CoUninitialize();

	return c;
}