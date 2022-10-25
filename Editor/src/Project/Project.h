#pragma once

class Project
{
public:

	void Save();

	std::string GetFilepath();

	Project(const std::string& Filepath);

private:
	
	std::string _Filepath;
};