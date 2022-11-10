#include "PCH/PCH.h"
#include "Project.h"

#include <windows.h>

#include "ProgressDialog/ProgressDialog.h"

void Project::Save()
{
	this->VML.Write(this->_Filepath);
}

std::string Project::GetFilepath()
{
	return this->_Filepath;
}

VL::Ref<Project> Project::Load(const std::string& Filepath)
{
	VL::Ref<Project> NewProject = VL::Ref<Project>(new Project());

	NewProject->_Filepath = Filepath;
	NewProject->VML = VL::VML(Filepath + "\\Volund.vproj");

	return NewProject;
}

VL::Ref<Project> Project::Create(const std::string& Filepath, const std::string& Name)
{
	VL::Ref<Project> NewProject = VL::Ref<Project>(new Project());

	NewProject->_Filepath = Filepath + "\\" + Name;

	ProgressDialog::Start([NewProject, Name]()
	{	
		std::filesystem::create_directory(NewProject->_Filepath);

		ProgressDialog::SetMessage("Creating directories...");

		std::string VendorPath = NewProject->_Filepath + "\\vendor";
		std::string PremakePath = VendorPath + "\\premake";
		std::string TempPath = NewProject->_Filepath + "\\temp";

		std::filesystem::create_directory(VendorPath);
		std::filesystem::create_directory(PremakePath);
		std::filesystem::create_directory(TempPath);

		ProgressDialog::SetMessage("Downloading premake...");

		std::string PremakeZipPath = TempPath + "\\premake5.zip";
		std::string CurlCommand = "curl -s -L https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip --output " + PremakeZipPath;
		std::string TarCommand = "tar.exe -xf " + PremakeZipPath + " -C " + TempPath;

		system(CurlCommand.c_str());
		system(TarCommand.c_str());

		std::filesystem::copy(PremakeZipPath, PremakePath + "\\premake5.exe");
		std::filesystem::remove_all(TempPath);

		ProgressDialog::SetMessage("Writing WML...");

		NewProject->VML.PushBack("Name", Name);

		NewProject->VML.Write(NewProject->_Filepath + "\\Volund.vproj");

		ProgressDialog::SetMessage("Done!");

	}, "Running Setup...");

	return NewProject;
}