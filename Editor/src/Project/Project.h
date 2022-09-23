#pragma once

namespace Volund
{
	class Project
	{
	public:

		void Save(const std::string& Filepath);

		void LoadScene(const std::string& Filepath);

		void SaveScene(const std::string& Filepath);
		
		std::string GetVMLFilepath();

		std::string GetSceneFilepath();

		const Volund::Ref<Volund::VML> GetVML() const;

		const Volund::Ref<Volund::Scene> GetScene() const;

		Project(const std::filesystem::path& Filepath);

	private:

		Volund::Ref<Volund::VML> _VML;

		Volund::Ref<Volund::Scene> _Scene;

		std::string _VMLFilepath;

		std::string _SceneFilepath;
	};
}
