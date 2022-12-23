#include "PCH/PCH.h"
#include "ImGuiModule.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_win32.h>

#include "ImGuiStyle.h"

#include "Application/Application.h"
#include "Application/Module/WindowModule/WindowModule.h"

#include <windows.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Volund
{
	void ImGuiModule::OnAttach(Application* App)
	{
		if (!App->HasModule<WindowModule>())
		{
			VOLUND_ERROR("Cant attach ImGuiModule to an app without a WindowModule!");
		}

		static std::string IniFilename = std::filesystem::current_path().string() + "\\imgui.ini";

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.IniFilename = IniFilename.c_str();

		auto AppWindow = App->GetModule<WindowModule>()->GetWindow();

		SetupImGuiStyle();

		ImGui_ImplWin32_Init(AppWindow->GetHandle());
		ImGui_ImplOpenGL3_Init();

		AppWindow->SetProcedureCatch((VL::ProcCatch)ImGui_ImplWin32_WndProcHandler);
	}

	void ImGuiModule::OnDetach()
	{

	}

	void ImGuiModule::Procedure(const Event& E)
	{
		VOLUND_PROFILE_FUNCTION();
	}

	bool ImGuiModule::BeginDockSpace()
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

	void ImGuiModule::BeginFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
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