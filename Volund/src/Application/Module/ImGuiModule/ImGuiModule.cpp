#include "PCH/PCH.h"
#include "ImGuiModule.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include "ImGuiStyle.h"

#include "Application/Application.h"
#include "Application/Module/WindowModule/WindowModule.h"

//#include <windows.h>

//extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Volund
{
	void ImGuiModule::OnAttach(Application* app)
	{
		if (!app->HasModule<WindowModule>())
		{
			VOLUND_ERROR("Cant attach ImGuiModule to an app without a WindowModule!");
		}

		static std::string iniFilename = std::filesystem::current_path().string() + "\\imgui.ini";

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.IniFilename = iniFilename.c_str();

		const auto appWindow = app->GetModule<WindowModule>()->GetWindow();

		SetupImGuiStyle();

		ImGui_ImplGlfw_InitForOpenGL(appWindow->GetGlfwWindow(), false);
		ImGui_ImplOpenGL3_Init();

		//appWindow->SetProcedureCatch((VL::ProcCatch)ImGui_ImplWin32_WndProcHandler);
	}

	void ImGuiModule::OnDetach()
	{

	}

	void ImGuiModule::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();
	}

	bool ImGuiModule::BeginDockSpace()
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

		if (ImGui::Begin("DockSpace Demo", &open, windowFlags))
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

	void ImGuiModule::BeginFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiModule::EndFrame()
	{
		ProgressDialog::Draw();
		TextInputDialog::Draw();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}