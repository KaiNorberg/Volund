#include "PCH/PCH.h"
#include "Project.h"

#include <windows.h>

void Project::Save()
{
	VL::VML VML;

	VL::VMLEntry Scenes;

	for (auto& [Filepath, Scene] : this->_Scenes)
	{
		Scenes.PushBack(Filepath);
	}
	VML.PushBack("Scenes", Scenes);

	for (auto& [Filepath, Scene] : this->_Scenes)
	{
		Scene->Serialize(Filepath);
	}
}

std::string Project::GetFilepath()
{
	return this->_Filepath;
}

VL::Ref<VL::Scene> Project::GetScene(const std::string& Filepath)
{
	if (this->_Scenes.contains(Filepath))
	{
		return this->_Scenes[Filepath];
	}
	else
	{
		return nullptr;
	}
}

std::unordered_map<std::string, VL::Ref<VL::Scene>>::iterator Project::begin()
{
	return this->_Scenes.begin();
}

std::unordered_map<std::string, VL::Ref<VL::Scene>>::iterator Project::end()
{
	return this->_Scenes.end();
}

std::unordered_map<std::string, VL::Ref<VL::Scene>>::const_iterator Project::begin() const
{
	return this->_Scenes.begin();
}

std::unordered_map<std::string, VL::Ref<VL::Scene>>::const_iterator Project::end() const
{
	return this->_Scenes.end();
}

Project::Project(const std::string& Filepath)
{
	std::filesystem::current_path(((std::filesystem::path)Filepath).parent_path());

	VL::VML VML = VL::VML(Filepath);

	VL::VMLEntry& Scenes = VML.Get("Scenes");

	for (int i = 0; i < Scenes.Size(); i++)
	{
		this->_Scenes[Scenes[i]] = VL::Scene::Deserialize(Scenes[i]);
	}
}
