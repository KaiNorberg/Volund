#include "PCH/PCH.h"
#include "ImGuiModule.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/imgui_internal.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

#include "Application/Application.h"

namespace Volund
{
	void ImGuiModule::OnAttach(Application* app)
	{
		static std::string iniFilename = fs::current_path().string() + "/imgui.ini";

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.IniFilename = iniFilename.c_str();

		const auto appWindow = app->GetWindow();

		ImGui_ImplGlfw_InitForOpenGL(appWindow->GetGlfwWindow(), false);
		ImGui_ImplOpenGL3_Init();

		appWindow->ConnectWindowFocusCallback(ImGui_ImplGlfw_WindowFocusCallback);
		appWindow->ConnectCursorEnterCallback(ImGui_ImplGlfw_CursorEnterCallback);
		appWindow->ConnectCursorPositionCallback(ImGui_ImplGlfw_CursorPosCallback);
		appWindow->ConnectMouseButtonCallback(ImGui_ImplGlfw_MouseButtonCallback);
		appWindow->ConnectScrollCallback(ImGui_ImplGlfw_ScrollCallback);
		appWindow->ConnectKeyCallback(ImGui_ImplGlfw_KeyCallback);
		appWindow->ConnectCharCallback(ImGui_ImplGlfw_CharCallback);
	}

	void ImGuiModule::OnDetach()
	{

	}

	void ImGuiModule::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (e.Type)
		{
		case VOLUND_EVENT_TYPE_RENDER:
		{
			this->BeginFrame();

			if (this->BeginDockSpace())
			{
				if (this->m_BackgroundCallback != nullptr)
				{
					this->m_BackgroundCallback();
				}

				for (auto& [typeID, imGuiWindows] : this->m_ImGuiWindows)
				{
					for (const auto& imGuiWindow : imGuiWindows)
					{
						imGuiWindow->Procedure(e);
					}
				}

			}

			ImGui::End();

			this->EndFrame();
		}
		break;
		default:
		{
			for (auto& [typeID, imGuiWindows] : this->m_ImGuiWindows)
			{
				for (const auto& imGuiWindow : imGuiWindows)
				{
					imGuiWindow->Procedure(e);
				}
			}
		}
		}
	}

	void ImGuiModule::SetBackgroundCallback(std::function<void()> callback)
	{
		this->m_BackgroundCallback = callback;
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

	void ImGuiModule::BeginFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiModule::EndFrame()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}