#include "PCH/PCH.h"
#include "Project.h"

namespace Volund
{
	void Project::Save(const std::string& Filepath)
	{
		if (!Filepath.empty())
		{
			this->_VML->Write(Filepath);
		}
	}

	void Project::LoadScene(const std::string& Filepath)
	{
		if (!Filepath.empty())
		{
			this->_Scene = Scene::Deserialize(Filepath);
		}
	}

	void Project::SaveScene(const std::string& Filepath)
	{
		if (!Filepath.empty())
		{
			this->_Scene->Serialize(Filepath);
		}
	}

	std::string Project::GetVMLFilepath()
	{
		return this->_VMLFilepath;
	}

	std::string Project::GetSceneFilepath()
	{
		return this->_SceneFilepath;
	}

	const Volund::Ref<Volund::VML> Project::GetVML() const
	{
		return this->_VML;
	}

	const Volund::Ref<Volund::Scene> Project::GetScene() const
	{
		return this->_Scene;
	}

	Project::Project(const std::filesystem::path& Filepath)
	{
		this->_VMLFilepath = Filepath.string();
		this->_VML = Volund::Ref<Volund::VML>(new VML(this->_VMLFilepath));

		std::filesystem::current_path(Filepath.parent_path());

		this->_SceneFilepath = this->_VML->Get("MainScene").String();
		this->_Scene = Scene::Deserialize(this->_SceneFilepath);
	}
}