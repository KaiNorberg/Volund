#include "PCH/PCH.h"
#include "Project.h"

#include <windows.h>

void Project::Save()
{
	VL::VML VML;

	VML.Write(this->_Filepath);
}

std::string Project::GetFilepath()
{
	return this->_Filepath;
}

Project::Project(const std::string& Filepath)
{
	this->_Filepath = Filepath;

	std::filesystem::current_path(((std::filesystem::path)Filepath).parent_path());

	VL::VML VML = VL::VML(Filepath);
}
