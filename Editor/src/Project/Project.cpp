#include "PCH/PCH.h"
#include "Project.h"

#include <windows.h>

bool Project::Loaded()
{
	return !this->_VMLFilepath.empty();
}

void Project::Save(const std::string& Filepath)
{
	if (!Filepath.empty())
	{
		this->_VML->Write(Filepath);
	}
}

void Project::Load(const std::filesystem::path& Filepath)
{
	this->_VMLFilepath = Filepath.string();
	this->_VML = VL::Ref<VL::VML>(new VL::VML(this->_VMLFilepath));

	std::filesystem::current_path(Filepath.parent_path());

	this->_SceneFilepath = this->_VML->Get("MainScene").String();
	this->_Scene = VL::Scene::Deserialize(this->_SceneFilepath);
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
				this->_Scene = VL::Scene::Deserialize(Filepath);
				this->_SceneFilepath = Filepath;

			}
			break;
			case IDNO:
			{
				this->_Scene = VL::Scene::Deserialize(Filepath);
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
			this->_Scene = VL::Scene::Deserialize(Filepath);
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

const VL::Ref<VL::VML> Project::GetVML() const
{
	return this->_VML;
}

const VL::Ref<VL::Scene> Project::GetScene() const
{
	return this->_Scene;
}