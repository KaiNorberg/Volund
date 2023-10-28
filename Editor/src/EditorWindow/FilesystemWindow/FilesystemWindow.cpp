#include "PCH/PCH.h"

#include "FilesystemWindow.h"

void FilesystemWindow::OnProcedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VOLUND_EVENT_TYPE_RENDER:
	{		
		auto assetManager = this->m_Context->GetAssetmanager();

		fs::path parentDir;
		if (assetManager != nullptr)
		{
			parentDir = assetManager->GetParentPath();
		}

		if (parentDir != this->m_OldParentDir)
		{
			this->m_CurrentDirectory = parentDir;
		}
		this->m_OldParentDir = parentDir;

		if (!fs::is_directory(parentDir))
		{
			break;
		}

		float cellSize = this->m_ThumbnailSize + this->m_Padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			ImGui::OpenPopup("Filesystem manip");
		}

		if (ImGui::BeginPopup("Filesystem manip"))
		{
			if (ImGui::BeginMenu("Create"))
			{
				if (ImGui::MenuItem("Folder"))
				{
					fs::path filepath = VL::Utils::GenerateUniquePath(this->m_CurrentDirectory / "New Folder");
					fs::create_directory(filepath);

					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Material"))
				{
					fs::path filepath = VL::Utils::GenerateUniquePath(this->m_CurrentDirectory / "New.material.lua");

					VL::Serializer serializer(VOLUND_SERIAL_FILE_TYPE_MATERIAL);
					serializer.StartTable();
					serializer.Insert("", "://Simple.shader");
					serializer.EndTable();
					serializer.WriteToFile(filepath.string());

					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Scene"))
				{
					fs::path filepath = VL::Utils::GenerateUniquePath(this->m_CurrentDirectory / "New.scene.lua");

					VL::Serializer serializer(VOLUND_SERIAL_FILE_TYPE_SCENE);
					serializer.StartTable();
					serializer.EndTable();
					serializer.WriteToFile(filepath.string());

					ImGui::CloseCurrentPopup();

					ImGui::CloseCurrentPopup();
				}
				ImGui::EndMenu();
			}

			ImGui::EndPopup();
		}

		ImGui::Columns(columnCount, 0, false);

		if (parentDir != this->m_CurrentDirectory && !this->m_ResourcesOpen)
		{
			this->ImGuiFilesystemEntry(this->m_CurrentDirectory.parent_path().string(), "../", true);
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

				this->ImGuiFilesystemEntry(key, fileName, false);
			}
		}
		else
		{
			for (auto& directory : fs::directory_iterator(this->m_CurrentDirectory))
			{
				if (!directory.is_directory())
				{
					continue;
				}

				auto filepath = directory.path();
				this->ImGuiFilesystemEntry(filepath.string(), filepath.filename().string(), true);
			}

			for (auto& file : fs::directory_iterator(this->m_CurrentDirectory))
			{
				if (file.is_directory())
				{
					continue;
				}

				auto filepath = file.path();
				this->ImGuiFilesystemEntry(filepath.string(), filepath.filename().string(), false);
			}
		}

		ImGui::Columns(1);
	}
	break;
	}
}

void FilesystemWindow::ImGuiFilesystemEntry(const std::string& payloadPath, const std::string& name, bool isDirectory)
{
	ImGui::PushID(payloadPath.c_str());

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
	ImGui::ImageButton(isDirectory ? (ImTextureID)m_DirectoryIcon->GetID() : (ImTextureID)m_FileIcon->GetID(), { this->m_ThumbnailSize, this->m_ThumbnailSize }, { 0, 1 }, { 1, 0 });
	ImGui::PopStyleColor();

	if (isDirectory)
	{
		ImGuiDragDropSource(VOLUND_IMGUI_DIRECTORY, payloadPath);
	}
	else
	{
		ImGuiDragDropSource(VOLUND_IMGUI_FILE, payloadPath);
	}

	if (isDirectory)
	{
		std::string filePayload = ImGuiDragDropTarget(VOLUND_IMGUI_FILE);
		if (!filePayload.empty())
		{
			fs::path sourcePath = filePayload;
			fs::path targetPath = fs::path(payloadPath) / sourcePath.filename().string();
			VOLUND_INFO("%s, %s", sourcePath.string().c_str(), targetPath.string().c_str());

			if (fs::exists(sourcePath))
			{
				fs::rename(sourcePath, targetPath);
			}
		}

		std::string directoryPayload = ImGuiDragDropTarget(VOLUND_IMGUI_DIRECTORY);
		if (!directoryPayload.empty())
		{
			fs::path sourcePath = directoryPayload;
			fs::path targetPath = payloadPath + VOLUND_PATH_SEPERATOR + sourcePath.filename().string();

			fs::create_directory(targetPath);	

			for (fs::path p : fs::recursive_directory_iterator(sourcePath))
			{
				fs::rename(p, targetPath / p.filename());
			}

			fs::remove(sourcePath);
		}
	}

	if (isDirectory)
	{
		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			this->m_CurrentDirectory = payloadPath;
		}
	}

	if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
	{
		ImGui::OpenPopup("File manip");
	}

	if (ImGui::BeginPopup("File manip"))
	{
		if (isDirectory)
		{

		}

		if (ImGui::MenuItem("Delete"))
		{
			if (fs::exists(payloadPath))
			{
				if (isDirectory)
				{
					for (fs::path p : fs::recursive_directory_iterator(payloadPath))
					{
						fs::remove(p);
					}
					fs::remove(payloadPath);
				}
				else
				{
					fs::remove(payloadPath);
				}
			}
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Rename"))
		{
			const std::string newName = VL::Dialog::InputBox("Rename", "Please specify a new name", "");
			if (newName != "")
			{
				fs::rename(payloadPath, fs::path(payloadPath).parent_path() / newName);
			}
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	ImGui::TextWrapped(name.c_str());

	ImGui::NextColumn();
	ImGui::PopID();
}

FilesystemWindow::FilesystemWindow(VL::Ref<EditorContext> context)
{
	this->SetName("Filesystem");

	this->m_Context = context;

	this->m_DirectoryIcon = VL::Texture::Create("data/icons/directory.png");
	this->m_FileIcon = VL::Texture::Create("data/icons/file.png");
}
