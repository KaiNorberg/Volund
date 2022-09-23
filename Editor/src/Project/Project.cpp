#include "PCH/PCH.h"
#include "Project.h"

#include <windows.h>

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
			if (this->_Scene != nullptr)
			{
				uint32_t Confirmation =
					MessageBox(NULL, (LPCWSTR)L"Do you wish to save the current scene?\nAny unsaved changes will be lost!",
						(LPCWSTR)L"Account Details", MB_ICONQUESTION | MB_YESNOCANCEL | MB_DEFBUTTON2);

				switch (Confirmation)
				{
				case IDYES:
				{
					this->_Scene->Serialize(this->_SceneFilepath);
					this->_Scene = Scene::Deserialize(Filepath);
					this->_SceneFilepath = Filepath;

				}
				break;
				case IDNO:
				{
					this->_Scene = Scene::Deserialize(Filepath);
					this->_SceneFilepath = Filepath;
				}
				break;
				default:
				{
				
				}
				break;
				}
			}
			else
			{
				this->_Scene = Scene::Deserialize(Filepath);
				this->_SceneFilepath = Filepath;
			}
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