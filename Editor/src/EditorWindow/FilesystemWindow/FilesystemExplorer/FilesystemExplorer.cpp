#include "PCH/PCH.h"
#include "FilesystemExplorer.h"

#include "Utils/Utils.h"

void FilesystemExplorer::Procedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VL::EventType::Render:
	{
		std::string scenePath = this->m_Context->GetFilepath();
		std::filesystem::path sceneDir = std::filesystem::path(scenePath).parent_path();

		//if (ImGui::BeginListBox(this->GetId().c_str(), ImVec2(-FLT_MIN, -FLT_MIN)))
		{
			if (std::filesystem::is_directory(sceneDir))
			{
				this->ImGuiDirectory(sceneDir, sceneDir);
			}
			//ImGui::EndListBox();
		}
	}
	break;
	case VL::EventType::Update:
	{
	}
	break;
	}
}

FilesystemExplorer::FilesystemExplorer(VL::Ref<EditorContext> context)
{
	this->m_Context = context;
}

void FilesystemExplorer::ImGuiDirectory(const std::filesystem::path& parentPath, const std::filesystem::path& path)
{
	std::string relativePath = std::filesystem::relative(path, parentPath).string();

	if (ImGui::TreeNodeEx(relativePath.c_str(), ImGuiTreeNodeFlags_Framed))
	{
		for (auto& entry : std::filesystem::directory_iterator(path))
		{
			if (entry.is_directory())
			{
				this->ImGuiDirectory(parentPath, entry);
			}
		}		
		for (auto& entry : std::filesystem::directory_iterator(path))
		{
			if (!entry.is_directory())
			{
				this->ImGuiFile(parentPath, entry);
			}
		}
		ImGui::TreePop();
	}
}

void FilesystemExplorer::ImGuiFile(const std::filesystem::path& parentPath, const std::filesystem::path& path)
{
	std::string relativePath = std::filesystem::relative(path, parentPath).string();

	ImGui::Selectable(relativePath.c_str());
}