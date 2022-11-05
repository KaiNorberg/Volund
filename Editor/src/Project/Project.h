#pragma once

class Project
{
public:

	void Save();

	std::string GetFilepath();

	VL::VML VML;

	static VL::Ref<Project> Load(const std::string& Filepath);

	static VL::Ref<Project> Create(const std::string& Filepath, const std::string& Name);

private:

	Project() = default;

	std::string _Filepath;
};