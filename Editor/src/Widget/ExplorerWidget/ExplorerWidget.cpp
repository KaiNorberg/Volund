#include "PCH/PCH.h"
#include "ExplorerWidget.h"

#include "Editor/Editor.h"

#include "ProgressDialog/ProgressDialog.h"
#include "TextInputDialog/TextInputDialog.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

#define PADDING 16.0f
#define THUMBNAIL_SIZE 128.0f

const char* ExplorerWidget::GetName()
{
	return "Explorer";
}

void ExplorerWidget::Draw(VL::TimeStep TS)
{
	if (ImGui::Begin("Explorer", &this->_IsActive))
	{
		if (this->_Editor->GetProject() != nullptr)
		{
			std::string ProjectFilepath = this->_Editor->GetProject()->GetFilepath() + "\\content";

			if (!this->_CurrentDirectory.string().starts_with(ProjectFilepath))
			{
				this->_CurrentDirectory = ProjectFilepath;
			}

			if (ImGui::BeginListBox("###ExplorerListBox", ImVec2(-FLT_MIN, -FLT_MIN)))
			{
				int ColumnCount = (int)(ImGui::GetContentRegionAvail().x / (PADDING + THUMBNAIL_SIZE));
				if (ColumnCount < 1)
				{
					ColumnCount = 1;
				}

				ImGui::Columns(ColumnCount, 0, false);

				if (this->_CurrentDirectory != ProjectFilepath)
				{
					this->DrawEntry("..", this->_CurrentDirectory.parent_path(), true);
				}

				for (auto& Entry : std::filesystem::directory_iterator(this->_CurrentDirectory))
				{
					if (Entry.is_directory())
					{
						this->DrawEntry(Entry.path().filename().string(), Entry.path(), true);
					}
				}
				for (auto& Entry : std::filesystem::directory_iterator(this->_CurrentDirectory))
				{
					if (!Entry.is_directory())
					{
						this->DrawEntry(Entry.path().filename().string(), Entry.path(), false);
					}
				}

				if (ImGui::BeginPopupContextWindow("ExplorerContext"))
				{
					if (this->_HoveredEntry.empty())
					{
						this->BackgroundContextMenu();
					}
					else
					{
						this->EntryContextMenu();
					}

					ImGui::EndPopup();
				}
				else
				{
					this->_HoveredEntry = "";
				}

				ImGui::Columns(1);

				ImGui::EndListBox();
			}
		}
		else
		{
			ImGui::Text("No Project Loaded!");
		}
	}

	ImGui::End();
}

ExplorerWidget::ExplorerWidget(Editor* editor, bool Active)
	: Widget(editor, Active)
{
	this->_FileIcon = VL::Texture::Create("data/icons/File.png");
	this->_FolderIcon = VL::Texture::Create("data/icons/Folder.png");
}

void ExplorerWidget::BackgroundContextMenu()
{
	if (ImGui::BeginMenu("New"))
	{
		if (ImGui::MenuItem("Folder"))
		{
			int i = 0;
			std::string NewFolder = this->_CurrentDirectory.string() + "\\NewFolder";
			while (std::filesystem::exists(NewFolder))
			{
				i++;
				NewFolder = this->_CurrentDirectory.string() + "\\NewFolder(" + std::to_string(i) + ")";
			}
			std::filesystem::create_directory(NewFolder);
		}
		if (ImGui::MenuItem("Component"))
		{

		}
		if (ImGui::MenuItem("Scene"))
		{

		}

		ImGui::EndMenu();
	}
}

void ExplorerWidget::EntryContextMenu()
{
	if (ImGui::MenuItem("Rename"))
	{
		std::filesystem::path Path = this->_HoveredEntry;
		TextInputDialog::Start([Path]()
		{
			std::filesystem::rename(Path, Path.parent_path().string() + "\\" + TextInputDialog::GetText());
		}, "Enter New Name");
	}
	if (ImGui::MenuItem("Delete"))
	{
		std::filesystem::remove_all(this->_HoveredEntry);
	}
}

void ExplorerWidget::DrawEntry(const std::string& Name, const std::filesystem::path& Path, bool IsDirectory)
{
	ImGui::PushID(Name.c_str());
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

	VL::Ref<VL::Texture> Icon = IsDirectory ? this->_FolderIcon : this->_FileIcon;
	ImGui::ImageButton((ImTextureID)Icon->GetID(), { THUMBNAIL_SIZE, THUMBNAIL_SIZE }, { 0, 1 }, { 1, 0 });

	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenBlockedByPopup | 
		ImGuiHoveredFlags_AllowWhenDisabled | ImGuiHoveredFlags_AllowWhenOverlapped))
	{
		this->_HoveredEntry = Path;
	}

	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	{
		if (IsDirectory)
		{
			this->_CurrentDirectory = Path;
		}
		else
		{

		}
	}

	ImGui::TextWrapped(Name.c_str());

	ImGui::NextColumn();
	ImGui::PopStyleColor();
	ImGui::PopID();
}
