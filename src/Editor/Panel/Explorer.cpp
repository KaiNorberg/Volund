#include "Explorer.h"

#include <imgui.h>

void Explorer::OnProcedure(const VL::Event& e)
{
	switch (e.type)
	{
	case VOLUND_EVENT_RENDER:
	{
		std::filesystem::path rootDir = this->m_Context->GameState->GetRootDirectory();

		if (rootDir != this->m_OldParentDir)
		{
			this->m_CurrentDirectory = rootDir;
		}
		this->m_OldParentDir = rootDir;

		if (!std::filesystem::is_directory(rootDir))
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
					std::filesystem::path filepath = VL::Utils::GenerateUniquePath(this->m_CurrentDirectory / "New Folder");
					std::filesystem::create_directory(filepath);

					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Material"))
				{
					std::filesystem::path filepath = VL::Utils::GenerateUniquePath(this->m_CurrentDirectory / "New.material.lua");

					VL::Serializer serializer(VOLUND_SERIAL_FILE_TYPE_MATERIAL);
					serializer.StartTable();
					serializer.Insert("", "://Simple.shader");
					serializer.EndTable();
					serializer.WriteToFile(filepath.string());

					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Scene"))
				{
					std::filesystem::path filepath = VL::Utils::GenerateUniquePath(this->m_CurrentDirectory / "New.scene.lua");

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

		if (rootDir != this->m_CurrentDirectory && !this->m_ResourcesOpen)
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
			for (auto& directory : std::filesystem::directory_iterator(this->m_CurrentDirectory))
			{
				if (!directory.is_directory())
				{
					continue;
				}

				auto filepath = directory.path();
				this->ImGuiFilesystemEntry(filepath.string(), filepath.filename().string(), true);
			}

			for (auto& file : std::filesystem::directory_iterator(this->m_CurrentDirectory))
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

void Explorer::ImGuiFilesystemEntry(std::string const& payloadPath, std::string const& name, bool isDirectory)
{
	ImGui::PushID(payloadPath.c_str());

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
	ImGui::ImageButton(isDirectory ? (ImTextureID)m_DirectoryIcon->GetID() : (ImTextureID)m_FileIcon->GetID(), { this->m_ThumbnailSize, this->m_ThumbnailSize }, { 0, 1 }, { 1, 0 });
	ImGui::PopStyleColor();

	if (isDirectory)
	{
		ImGuiDragDropSource(IMGUI_DRAG_DROP_DIR, payloadPath);
	}
	else
	{
		ImGuiDragDropSource(IMGUI_DRAG_DROP_FILE, payloadPath);
	}

	if (isDirectory)
	{
		std::string filePayload = ImGuiDragDropTarget(IMGUI_DRAG_DROP_FILE);
		if (!filePayload.empty())
		{
			std::filesystem::path sourcePath = filePayload;
			std::filesystem::path targetPath = std::filesystem::path(payloadPath) / sourcePath.filename().string();
			VOLUND_INFO("%s, %s", sourcePath.string().c_str(), targetPath.string().c_str());

			if (std::filesystem::exists(sourcePath))
			{
				std::filesystem::rename(sourcePath, targetPath);
			}
		}

		std::string directoryPayload = ImGuiDragDropTarget(IMGUI_DRAG_DROP_DIR);
		if (!directoryPayload.empty())
		{
			std::filesystem::path sourcePath = directoryPayload;
			std::filesystem::path targetPath = payloadPath + VOLUND_PATH_SEPERATOR + sourcePath.filename().string();

			std::filesystem::create_directory(targetPath);

			for (std::filesystem::path p : std::filesystem::recursive_directory_iterator(sourcePath))
			{
				std::filesystem::rename(p, targetPath / p.filename());
			}

			std::filesystem::remove(sourcePath);
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
			if (std::filesystem::exists(payloadPath))
			{
				if (isDirectory)
				{
					for (std::filesystem::path p : std::filesystem::recursive_directory_iterator(payloadPath))
					{
						std::filesystem::remove(p);
					}
					std::filesystem::remove(payloadPath);
				}
				else
				{
					std::filesystem::remove(payloadPath);
				}
			}
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Rename"))
		{
			const std::string newName = VL::Dialog::InputBox("Rename", "Please specify a new name", "");
			if (newName != "")
			{
				std::filesystem::rename(payloadPath, std::filesystem::path(payloadPath).parent_path() / newName);
			}
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	ImGui::TextWrapped(name.c_str());

	ImGui::NextColumn();
	ImGui::PopID();
}

Explorer::Explorer(std::shared_ptr<EditorContext> context)
{
	this->SetName("Filesystem");

	this->m_Context = context;

	this->m_DirectoryIcon = VL::Texture::Create("data/icons/directory.png");
	this->m_FileIcon = VL::Texture::Create("data/icons/file.png");
}
