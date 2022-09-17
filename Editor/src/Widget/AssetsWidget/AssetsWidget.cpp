#include "PCH/PCH.h"
#include "AssetsWidget.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

#include "Editor/EditorLayer/EditorLayer.h"

const char* AssetsWidget::GetName()
{
	return "Assets";
}

void AssetsWidget::OnUpdate()
{
	auto Scene = this->_Parent->GetLayer<EditorLayer>()->GetScene();

	if (ImGui::Begin("Assets", &this->_IsActive))
	{
		if (Scene != nullptr)
		{
			this->DrawAssetTab(Scene);

			ImGui::NewLine();

			this->DrawFileExplorer(Scene);
		}
		else
		{
			ImGui::Text("No Scene Loaded!");
		}
	}

	ImGui::End();
}

void AssetsWidget::DrawAssetTab(Volund::Ref<Volund::Scene> Scene)
{
	if (ImGui::BeginListBox("##AssetList", ImVec2(-FLT_MIN, -ImGui::GetContentRegionAvail().y / 2)))
	{
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() - 35);

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));

		if (Scene->Assets.HasType<Volund::MeshAsset>())
		{
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Meshes");
			ImGui::Separator();
			ImGui::Columns(2);

			for (auto& Asset : Scene->Assets.View<Volund::MeshAsset>())
			{
				ImGui::Text(Asset->GetFilePath().c_str());
				ImGui::NextColumn();

				ImGui::PushID(Asset.get());

				if (ImGui::Button("X"))
				{
					if (Asset.use_count() <= 2)
					{
						Scene->Assets.Erase<Volund::MeshAsset>(std::dynamic_pointer_cast<Volund::MeshAsset>(Asset));
						ImGui::PopID();
						break;
					}
					else
					{
						VOLUND_WARNING("Asset is still being used by entities!");
					}
				}

				ImGui::PopID();

				ImGui::NextColumn();
			}
		}
		if (Scene->Assets.HasType<Volund::MaterialAsset>())
		{
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Materials");
			ImGui::Separator();
			ImGui::Columns(2);

			for (auto& Asset : Scene->Assets.View<Volund::MaterialAsset>())
			{
				ImGui::Text(Asset->GetFilePath().c_str());
				ImGui::NextColumn();

				ImGui::PushID(Asset.get());

				if (ImGui::Button("X"))
				{
					if (Asset.use_count() <= 2)
					{
						Scene->Assets.Erase<Volund::MaterialAsset>(std::dynamic_pointer_cast<Volund::MaterialAsset>(Asset));
						ImGui::PopID();
						break;
					}
					else
					{
						VOLUND_WARNING("Asset is still being used by entities!");
					}
				}

				ImGui::PopID();

				ImGui::NextColumn();
			}
		}
		if (Scene->Assets.HasType<Volund::TextureAsset>())
		{
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Textures");
			ImGui::Separator();
			ImGui::Columns(2);

			for (auto& Asset : Scene->Assets.View<Volund::TextureAsset>())
			{
				ImGui::Text(Asset->GetFilePath().c_str());
				ImGui::NextColumn();

				ImGui::PushID(Asset.get());

				if (ImGui::Button("X"))
				{
					if (Asset.use_count() <= 2)
					{
						Scene->Assets.Erase<Volund::TextureAsset>(std::dynamic_pointer_cast<Volund::TextureAsset>(Asset));
						ImGui::PopID();
						break;
					}
					else
					{
						VOLUND_WARNING("Asset is still being used by entities!");
					}
				}

				ImGui::PopID();

				ImGui::NextColumn();
			}
		}
		if (Scene->Assets.HasType<Volund::ShaderAsset>())
		{
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Shaders");
			ImGui::Separator();
			ImGui::Columns(2);

			for (auto& Asset : Scene->Assets.View<Volund::ShaderAsset>())
			{
				ImGui::Text(Asset->GetFilePath().c_str());
				ImGui::NextColumn();

				ImGui::PushID(Asset.get());

				if (ImGui::Button("X"))
				{
					if (Asset.use_count() <= 2)
					{
						Scene->Assets.Erase<Volund::ShaderAsset>(std::dynamic_pointer_cast<Volund::ShaderAsset>(Asset));
						ImGui::PopID();
						break;
					}
					else
					{
						VOLUND_WARNING("Asset is still being used by entities!");
					}
				}

				ImGui::PopID();

				ImGui::NextColumn();
			}

			ImGui::PopStyleColor(3);

			ImGui::Columns(1);
		}
		ImGui::EndListBox();
	}
}

void AssetsWidget::DrawFileExplorer(Volund::Ref<Volund::Scene> Scene)
{
	if (ImGui::BeginListBox("##FileExplorer", ImVec2(-FLT_MIN, ImGui::GetContentRegionAvail().y)))
	{
		this->DrawDirectory(Scene, std::filesystem::current_path());

		ImGui::EndListBox();
	}
}

void AssetsWidget::DrawDirectory(Volund::Ref<Volund::Scene> Scene, std::filesystem::path DirectoryPath)
{
	for (const auto& Directory : std::filesystem::directory_iterator(DirectoryPath))
	{
		if (Directory.is_directory())
		{
			std::string DirectoryName = Directory.path().filename().string();

			if (ImGui::TreeNode(DirectoryName.c_str(), DirectoryName.c_str()))
			{
				this->DrawDirectory(Scene, Directory.path());
				ImGui::TreePop();
			}
		}
	}

	for (const auto& File : std::filesystem::directory_iterator(DirectoryPath))
	{
		if (!File.is_directory())
		{
			std::string FileName = File.path().filename().string();

			if (File.path().extension() == ".vmaterial" || File.path().extension() == ".vshader" || 
				File.path().extension() == ".obj" || 
				File.path().extension() == ".jpg" || File.path().extension() == ".png" || File.path().extension() == ".bmp")
			{
				if (ImGui::Button(FileName.c_str()))
				{
					if (Scene != nullptr)
					{
						std::string RelativePath = std::filesystem::relative(File.path(), std::filesystem::current_path()).string();
						Scene->CreateAsset(RelativePath);
					}
				}
			}
		}
	}
}

AssetsWidget::AssetsWidget(Volund::Layer* Parent)
{
	this->_Parent = Parent;
}
