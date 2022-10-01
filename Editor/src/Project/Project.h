#pragma once

class Project
{
public:

	bool Loaded();

	void Save(const std::string& Filepath);

	void Load(const std::filesystem::path& Filepath);

	bool SceneLoaded();

	void LoadScene(const std::string& Filepath);

	void SaveScene(const std::string& Filepath);
		
	std::string GetVMLFilepath();

	std::string GetSceneFilepath();

	const VL::Ref<VL::VML> GetVML() const;

	const VL::Ref<VL::Scene> GetScene() const;

private:

	VL::Ref<VL::VML> _VML;

	VL::Ref<VL::Scene> _Scene;

	std::string _VMLFilepath;

	std::string _SceneFilepath;
};