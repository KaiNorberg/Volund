#pragma once

class Project
{
public:

	void Save();

	std::string GetFilepath();

	VL::Ref<VL::Scene> GetScene(const std::string& Filepath);

	std::unordered_map<std::string, VL::Ref<VL::Scene>>::iterator begin();
	std::unordered_map<std::string, VL::Ref<VL::Scene>>::iterator end();

	std::unordered_map<std::string, VL::Ref<VL::Scene>>::const_iterator begin() const;
	std::unordered_map<std::string, VL::Ref<VL::Scene>>::const_iterator end() const;

	Project(const std::string& Filepath);

private:
	
	std::unordered_map<std::string, VL::Ref<VL::Scene>> _Scenes;

	std::string _Filepath;
};