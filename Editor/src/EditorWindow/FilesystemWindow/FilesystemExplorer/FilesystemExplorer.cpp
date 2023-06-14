#include "PCH/PCH.h"
#include "FilesystemExplorer.h"

#include "Utils/Utils.h"

void FilesystemExplorer::Procedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VL::EventType::Render:
	{
		std::filesystem::path parentDir = this->m_Context->GetParentPath();

		if (parentDir != this->m_OldParentDir)
		{
			this->m_RelativeDirectory = "";
		}
		this->m_OldParentDir = parentDir;

		if (!std::filesystem::is_directory(parentDir))
		{
			break;
		}

		std::filesystem::path currentDirectory = parentDir;
		currentDirectory /= this->m_RelativeDirectory;

		float cellSize = this->m_ThumbnailSize + this->m_Padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

		if (!this->m_RelativeDirectory.empty())
		{
			this->ImGuiDirectory(this->m_RelativeDirectory.parent_path(), "../");
		}

		for (auto& directory : std::filesystem::directory_iterator(currentDirectory))
		{
			if (!directory.is_directory())
			{
				continue;
			}

			this->ImGuiDirectory(directory.path());
		}

		for (auto& file : std::filesystem::directory_iterator(currentDirectory))
		{
			if (file.is_directory())
			{
				continue;
			}

			this->ImGuiFile(file);
		}

		ImGui::Columns(1);				
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

	this->m_DirectoryIcon = VL::Texture::CreateAsync("data/icons/directory.png");
	this->m_FileIcon = VL::Texture::CreateAsync("data/icons/file.png");
}

void FilesystemExplorer::ImGuiDirectory(const std::filesystem::path& path, const char* name)
{
	std::filesystem::path parentDir = this->m_Context->GetParentPath();

	std::string filenameString = path.filename().string();

	ImGui::PushID(filenameString.c_str());

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
	ImGui::ImageButton((ImTextureID)m_DirectoryIcon->GetID(), { this->m_ThumbnailSize, this->m_ThumbnailSize }, { 0, 1 }, { 1, 0 });
	ImGui::PopStyleColor();

	if (ImGui::BeginDragDropSource())
	{
		const char* itemPath = path.string().c_str();
		ImGui::Text(itemPath);
		ImGui::SetDragDropPayload(EDITOR_FILESYSTEM_DIRECTORY, itemPath, (std::strlen(itemPath) + 1) * sizeof(char));
		ImGui::EndDragDropSource();
	}

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* filePayload = ImGui::AcceptDragDropPayload(EDITOR_FILESYSTEM_FILE);
		const ImGuiPayload* directoryPayload = ImGui::AcceptDragDropPayload(EDITOR_FILESYSTEM_DIRECTORY);

		if (filePayload != nullptr)
		{
			std::filesystem::path sourcePath = parentDir;
			sourcePath /= (const char*)filePayload->Data;

			std::filesystem::path targetPath = parentDir;
			targetPath /= path;
			targetPath /= sourcePath.filename();

			std::filesystem::rename(sourcePath, targetPath);
		}

		if (directoryPayload != nullptr)
		{
			std::filesystem::path sourcePath = (const char*)directoryPayload->Data;

			std::filesystem::path targetPath = parentDir;
			targetPath /= path;
			targetPath /= sourcePath.filename();

			std::filesystem::create_directory(targetPath);

			for (std::filesystem::path p : std::filesystem::recursive_directory_iterator(sourcePath))
			{
				std::filesystem::rename(p, targetPath / p.filename());
			}

			std::filesystem::remove(sourcePath);
		}

		ImGui::EndDragDropTarget();
	}

	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	{
		this->m_RelativeDirectory = std::filesystem::relative(path, parentDir);
	}

	if (name != nullptr)
	{
		ImGui::TextWrapped(name);
	}
	else
	{
		ImGui::TextWrapped(filenameString.c_str());
	}

	ImGui::NextColumn();
	ImGui::PopID();
}

void FilesystemExplorer::ImGuiFile(const std::filesystem::path& path)
{
	std::filesystem::path parentDir = this->m_Context->GetParentPath();

	std::string filenameString = path.filename().string();

	ImGui::PushID(filenameString.c_str());

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
	ImGui::ImageButton((ImTextureID)m_FileIcon->GetID(), { this->m_ThumbnailSize, this->m_ThumbnailSize }, { 0, 1 }, { 1, 0 });
	ImGui::PopStyleColor();

	if (ImGui::BeginDragDropSource())
	{
		std::string relativePathString = VL::Utils::RelativePath(path, parentDir).string();
		const char* itemPath = relativePathString.c_str();
		ImGui::Text(itemPath);
		ImGui::SetDragDropPayload(EDITOR_FILESYSTEM_FILE, itemPath, (std::strlen(itemPath) + 1) * sizeof(char));
		ImGui::EndDragDropSource();
	}

	ImGui::TextWrapped(filenameString.c_str());

	ImGui::NextColumn();
	ImGui::PopID();
}
