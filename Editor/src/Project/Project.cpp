#include "PCH/PCH.h"
#include "Project.h"

#include <windows.h>

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
	NewProject->VML = VL::VML(Filepath);

	return NewProject;
}

VL::Ref<Project> Project::Create(const std::string& Filepath, const std::string& Name)
{
	VL::Ref<Project> NewProject = VL::Ref<Project>(new Project());

	NewProject->_Filepath = Filepath + "/" + Name;

	std::filesystem::create_directory(NewProject->_Filepath);

	

	NewProject->VML.Write(NewProject->_Filepath + "/" + Name + ".vproj");

	return NewProject;
}
