#include "PCH/PCH.h"

#include "Editor.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_win32.h>

#include <windows.h>

void Editor::OnRun()
{
	VL::RenderingAPI::Select(VL::GraphicsAPI::OPENGL);

	this->AttachModule(new VL::WindowModule());
	this->AttachModule(new VL::ImGuiModule());

	VL::RenderingAPI::Init();
	VL::Renderer::Init(new VL::ForwardRenderer());

	//ImGuiIO& io = ImGui::GetIO();
	//io.Fonts->AddFontFromFileTTF("data/fonts/OpenSans-Regular.ttf", 18.0f);

	this->GetModule<VL::WindowModule>()->Window->Show();
}

void Editor::OnTerminate()
{

}

void Editor::OnUpdate(VL::TimeStep TS)
{
	auto WindowModule = this->GetModule<VL::WindowModule>();

	WindowModule->Context->MakeCurrent();

	this->Draw(TS);

	WindowModule->Context->Flush();

	VL::RenderingAPI::Clear();
}

void Editor::OnEvent(VL::Event* E)
{
	this->_Input.HandleEvent(E);

	this->HandleShortcuts();
}

void Editor::CreateProject(const std::string& Filepath, const std::string& Name)
{
	if (Filepath.empty() || Name.empty())
	{
		return;
	}

	ProgressDialog::Start([Filepath, Name]()
	{
		ProgressDialog::SetMessage("Creating directories...");

		std::string FinalPath = Filepath + "\\" + Name;

		std::filesystem::create_directory(FinalPath);

		std::string VendorPath = FinalPath + "\\vendor";
		std::string SourcePath = FinalPath + "\\src";
		std::string PremakePath = VendorPath + "\\premake";
		std::string TempPath = FinalPath + "\\temp";

		std::filesystem::create_directory(VendorPath);
		std::filesystem::create_directory(SourcePath);
		std::filesystem::create_directory(PremakePath);
		std::filesystem::create_directory(TempPath);

		std::string PremakeZipPath = TempPath + "\\premake5.zip";

		ProgressDialog::SetMessage("Downloading premake...");

		std::string CurlCommand = "curl -s -L https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip --output " + PremakeZipPath;
		system(CurlCommand.c_str());

		ProgressDialog::SetMessage("Installing premake...");

		std::string TarCommand = "tar.exe -xf " + PremakeZipPath + " -C " + TempPath;
		system(TarCommand.c_str());
		std::filesystem::copy(TempPath + "\\premake5.exe", PremakePath + "\\premake5.exe");

		ProgressDialog::SetMessage("Copying files...");

		std::filesystem::copy("data\\templates\\premake5.lua", FinalPath + "\\premake5.lua");

		ProgressDialog::SetMessage("Running Premake...");

		std::filesystem::path CurrentPath = std::filesystem::current_path();

		std::filesystem::current_path(FinalPath);

		std::string PremakeCommand = "vendor\\premake\\premake5.exe vs2022";
		system(PremakeCommand.c_str());

		std::filesystem::current_path(CurrentPath);

		ProgressDialog::SetMessage("Clean up...");

		std::filesystem::remove_all(TempPath);

		ProgressDialog::SetMessage("Done!");

	}, "Creating Project...");
}

void Editor::Draw(VL::TimeStep TS)
{
	VL::ImGuiModule::StartFrame();

	VL::RenderingAPI::Clear(VL::RGBA(0.2f, 0.2f, 0.2f, 1.0f));

	if (VL::ImGuiModule::BeginDockSpace())
	{
		this->DrawMenuBar();
	}

	ImGui::End();

	VL::ImGuiModule::EndFrame();
}

void Editor::DrawMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Project"))
		{
			if (ImGui::MenuItem("New"))
			{
				TextInputDialog::Start([this]()
				{
					this->CreateProject(FileDialog::OpenFolder(), TextInputDialog::GetText());
				}, "Enter Project Name:");
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

void Editor::HandleShortcuts()
{
	if (this->_Input.IsHeld(VOLUND_KEY_SHIFT))
	{

	}
}