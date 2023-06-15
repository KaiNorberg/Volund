#include "PCH/PCH.h"

#include "FilesystemWindow.h"

void FilesystemWindow::OnProcedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VL::EventType::Render:
	{
		std::filesystem::path parentDir = this->m_Context->GetParentPath();

		if (parentDir != this->m_OldParentDir)
		{
			this->m_CurrentDirectory = parentDir;
		}
		this->m_OldParentDir = parentDir;

		if (!std::filesystem::is_directory(parentDir))
		{
			break;
		}

		float cellSize = this->m_ThumbnailSize + this->m_Padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

		if (parentDir != this->m_CurrentDirectory && !this->m_ResourcesOpen)
		{
			this->ImGuiDirectory(this->m_CurrentDirectory.parent_path().string(), "../");
		}
		else
		{
			ImGui::PushID("://");

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			ImGui::ImageButton((ImTextureID)m_DirectoryIcon->GetID(), { this->m_ThumbnailSize, this->m_ThumbnailSize }, { 0, 1 }, { 1, 0 });
			ImGui::PopStyleColor();

			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				this->m_ResourcesOpen = !this->m_ResourcesOpen;
			}

			if (this->m_ResourcesOpen)
			{
				ImGui::TextWrapped("../");
			}
			else
			{
				ImGui::TextWrapped("://");
			}

			ImGui::NextColumn();
			ImGui::PopID();
		}

		if (this->m_ResourcesOpen)
		{
			for (auto& [key, value] : VL::ResourceLibrary::Map())
			{
				std::string fileName = key;
				if (fileName.starts_with("://"))
				{
					fileName.erase(fileName.begin(), fileName.begin() + 3);
				}

				this->ImGuiFile(key, fileName);
			}
		}
		else
		{
			for (auto& directory : std::filesystem::directory_iterator(this->m_CurrentDirectory))
			{
				if (!directory.is_directory())
				{
					continue;
				}

				auto filepath = directory.path();
				this->ImGuiDirectory(filepath.string(), filepath.filename().string());
			}

			for (auto& file : std::filesystem::directory_iterator(this->m_CurrentDirectory))
			{
				if (file.is_directory())
				{
					continue;
				}

				auto filepath = file.path();
				this->ImGuiFile(filepath.string(), filepath.filename().string());
			}
		}

		ImGui::Columns(1);
	}
	break;
	}
}

void FilesystemWindow::ImGuiDirectory(const std::string& payloadPath, const std::string& name)
{
	ImGui::PushID(payloadPath.c_str());

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
	ImGui::ImageButton((ImTextureID)m_DirectoryIcon->GetID(), { this->m_ThumbnailSize, this->m_ThumbnailSize }, { 0, 1 }, { 1, 0 });
	ImGui::PopStyleColor();

	if (ImGui::BeginDragDropSource())
	{
		const char* itemPath = payloadPath.c_str();
		ImGui::Text(itemPath);
		ImGui::SetDragDropPayload(VOLUND_IMGUI_DIRECTORY, itemPath, (std::strlen(itemPath) + 1) * sizeof(char));
		ImGui::EndDragDropSource();
	}

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* filePayload = ImGui::AcceptDragDropPayload(VOLUND_IMGUI_FILE);
		if (filePayload != nullptr)
		{
			std::filesystem::path sourcePath = (const char*)filePayload->Data;
			std::filesystem::path targetPath = payloadPath + "/" + sourcePath.filename().string();

			if (std::filesystem::exists(sourcePath) && std::filesystem::exists(targetPath))
			{
				std::filesystem::rename(sourcePath, targetPath);
			}
		}

		const ImGuiPayload* directoryPayload = ImGui::AcceptDragDropPayload(VOLUND_IMGUI_DIRECTORY);
		if (directoryPayload != nullptr)
		{
			std::filesystem::path sourcePath = (const char*)directoryPayload->Data;
			std::filesystem::path targetPath = payloadPath + "/" + sourcePath.filename().string();

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
		this->m_CurrentDirectory = payloadPath;
	}

	ImGui::TextWrapped(name.c_str());

	ImGui::NextColumn();
	ImGui::PopID();
}

void FilesystemWindow::ImGuiFile(const std::string& payloadPath, const std::string& name)
{
	ImGui::PushID(payloadPath.c_str());

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
	ImGui::ImageButton((ImTextureID)m_FileIcon->GetID(), { this->m_ThumbnailSize, this->m_ThumbnailSize }, { 0, 1 }, { 1, 0 });
	ImGui::PopStyleColor();

	if (ImGui::BeginDragDropSource())
	{
		const char* itemPath = payloadPath.c_str();
		ImGui::Text(itemPath);
		ImGui::SetDragDropPayload(VOLUND_IMGUI_FILE, itemPath, (std::strlen(itemPath) + 1) * sizeof(char));
		ImGui::EndDragDropSource();
	}

	ImGui::TextWrapped(name.c_str());

	ImGui::NextColumn();
	ImGui::PopID();
}

FilesystemWindow::FilesystemWindow(VL::Ref<EditorContext> context)
{
	this->SetName("Filesystem");

	this->m_Context = context;

	this->m_DirectoryIcon = VL::Texture::CreateAsync("data/icons/directory.png");
	this->m_FileIcon = VL::Texture::CreateAsync("data/icons/file.png");
}
