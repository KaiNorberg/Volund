#include "PCH/PCH.h"
#include "AssetWidget.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

#include "Editor/Editor.h"

const char* AssetWidget::GetName()
{
	return "AssetWidget";
}

void AssetWidget::Draw(VL::TimeStep TS)
{
	if (ImGui::Begin("Assets", &this->_IsActive))
	{
		if (ImGui::BeginListBox("###AssetsList", ImVec2(-FLT_MIN, -FLT_MIN)))
		{
			std::filesystem::path CurrentPath = std::filesystem::current_path();
			std::string PathName = CurrentPath.filename().string();

			if (ImGui::TreeNode(":/"))
			{
				this->DrawResource(VL::Filesystem::GetGrandFatherResource());

				ImGui::TreePop();
			}

			if (ImGui::TreeNode(PathName.c_str()))
			{
				this->DrawDirectory(CurrentPath);

				ImGui::TreePop();
			}

			ImGui::EndListBox();
		}
	}

	ImGui::End();
}

void AssetWidget::DrawResource(const VL::Resource* Resource)
{
	for (auto& [ChildName, ChildResource] : (*Resource))
	{
		{
			HandleResourceEntry(ChildName, &ChildResource);
		}
	}
}

void AssetWidget::DrawDirectory(const std::filesystem::path& Directory)
{
	for (auto& Directory : std::filesystem::directory_iterator(Directory))
	{
		if (Directory.is_directory())
		{
			HandleDirectoryEntry(Directory);
		}
	}

	for (auto& File : std::filesystem::directory_iterator(Directory))
	{
		if (!File.is_directory())
		{
			HandleDirectoryEntry(File);
		}
	}
}

void AssetWidget::HandleResourceEntry(const std::string& Name, const VL::Resource* Resource)
{
	static std::filesystem::path SelectedName;

	if (Resource->IsDirectory())
	{
		if (ImGui::TreeNode(Name.c_str()))
		{
			this->DrawResource(Resource);

			ImGui::TreePop();
		}
	}
	else
	{
		bool Selected = SelectedName == Name;

		if (ImGui::Selectable(Name.c_str(), Selected))
		{
			SelectedName = Name;
		}

		if (Selected)
		{
			if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{

			}
		}
	}
}

void AssetWidget::HandleDirectoryEntry(const std::filesystem::directory_entry& Entry)
{
	static std::filesystem::path SelectedPath;

	std::filesystem::path Path = Entry.path();
	std::string FileName = Path.filename().string();

	if (Entry.is_directory())
	{
		if (ImGui::TreeNode(FileName.c_str()))
		{
			this->DrawDirectory(Path);

			ImGui::TreePop();
		}
	}
	else
	{
		bool Selected = SelectedPath == Path;

		if (ImGui::Selectable(FileName.c_str(), Selected))
		{
			SelectedPath = Path;
		}

		if (Selected)
		{
			if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (Path.extension() == ".vscene")
				{
					this->_Editor->LoadScene(Path.string());
				}
			}
		}
	}
}
