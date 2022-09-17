#include "PCH/PCH.h"
#include "SceneWidget.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

#include "Editor/EditorLayer/EditorLayer.h"

const char* SceneWidget::GetName()
{
	return "Scene";
}

void SceneWidget::OnUpdate()
{
	auto Scene = this->_Parent->GetLayer<EditorLayer>()->GetScene();

	if (ImGui::Begin("Scene", &this->_IsActive))
	{
		ImGui::BeginTabBar("##SceneTabs");

		bool EntityTabSelected = false;

		if (ImGui::BeginTabItem("Entities"))
		{
			EntityTabSelected = true;

			if (Scene != nullptr)
			{
				this->DrawEntityTab(Scene);
			}
			
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Assets"))
		{
			bool EntityTabSelected = false;

			if (Scene != nullptr)
			{
				this->DrawAssetTab(Scene);
			}

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();

		if (EntityTabSelected)
		{
			if (Scene != nullptr)
			{
				if (Scene->HasEntity(this->_SelectedEntity))
				{
					this->DrawInspector(Scene->GetEntity(this->_SelectedEntity), Scene);
				}
			}
		}
		else
		{
			this->DrawFileExplorer(Scene);
		}
	}

	ImGui::End();
}

void SceneWidget::DrawEntityTab(Volund::Ref<Volund::Scene> Scene)
{
	if (ImGui::Button("+"))
	{
		std::string EntityName = "NewEntity";
		int i = 0;
		while (true)
		{
			if (!Scene->HasEntity(EntityName + std::to_string(i)))
			{
				Scene->CreateEntity(EntityName + std::to_string(i));
				break;
			}
			i++;
		}
	}
	ImGui::SameLine();

	static char SearchTerm[64];
	ImGui::Text("Search: ");
	ImGui::SameLine();
	ImGui::InputText(" ", SearchTerm, 64);

	if (ImGui::BeginListBox(" ", ImVec2(-FLT_MIN, -ImGui::GetContentRegionAvail().y / 2)))
	{
		if (Scene != nullptr)
		{
			for (auto& Entity : (*Scene.get()))
			{
				if (Entity->GetName().find(SearchTerm) != std::string::npos)
				{
					this->DrawEntityNode(Entity);
				}
			}
		}
		ImGui::EndListBox();
	}
}

void SceneWidget::DrawAssetTab(Volund::Ref<Volund::Scene> Scene)
{
	if (ImGui::BeginListBox(" ", ImVec2(-FLT_MIN, -ImGui::GetContentRegionAvail().y / 2)))
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

void SceneWidget::DrawEntityNode(Volund::Ref<Volund::Entity> Entity)
{
	ImGui::PushID((void*)Entity.get());

	std::string EntityName = Entity->GetName();

	bool Open = false;
	if (EntityName == _SelectedEntity)
	{
		Open = ImGui::TreeNodeEx((void*)Entity.get(), ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow, EntityName.c_str());
	}
	else
	{
		Open = ImGui::TreeNodeEx((void*)Entity.get(), ImGuiTreeNodeFlags_OpenOnArrow, EntityName.c_str());
	}
	
	if (ImGui::IsItemClicked())
	{
		_SelectedEntity = EntityName;
	}

	if (Open)
	{
		ImGui::TreePop();
	}

	ImGui::PopID();
}

void SceneWidget::DrawFileExplorer(Volund::Ref<Volund::Scene> Scene)
{
	if (ImGui::BeginListBox(" ", ImVec2(-FLT_MIN, ImGui::GetContentRegionAvail().y)))
	{
		this->DrawDirectory(Scene, std::filesystem::current_path());

		ImGui::EndListBox();
	}
}

void SceneWidget::DrawDirectory(Volund::Ref<Volund::Scene> Scene, std::filesystem::path DirectoryPath)
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

			if (ImGui::Button(FileName.c_str()))
			{
				if (File.path().extension() == ".vscene")
				{
					std::string RelativePath = std::filesystem::relative(File.path(), std::filesystem::current_path()).string();

					this->_Parent->GetLayer<EditorLayer>()->LoadScene(RelativePath);
				}				
				else
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

void SceneWidget::DrawInspector(Volund::Ref<Volund::Entity> Entity, Volund::Ref<Volund::Scene> Scene)
{
	std::string EntityName = Entity->GetName();
	ImGui::InputText("##EntityName", &EntityName);
	if (EntityName != Entity->GetName())
	{
		_SelectedEntity = EntityName;
		Entity->SetName(EntityName);
	}

	if (Entity->HasComponent<Volund::Transform>())
	{
		auto& View = Entity->ComponentView<Volund::Transform>();
		this->DrawComponentView(View, "Transform", [this](Volund::Ref<Volund::Component> Component)
		{
			auto Transform = std::dynamic_pointer_cast<Volund::Transform>(Component);
			Volund::Vec3 Position = Transform->Position;
			Volund::Vec3 Rotation = Transform->GetRotation();
			Volund::Vec3 Scale = Transform->Scale;

			Vec3Control("Position", &Position, 0.1f, 0.0f);
			Vec3Control("Rotation", &Rotation, 0.1f, 0.0f);
			Vec3Control("Scale", &Scale, 0.1f, 1.0f);

			Transform->Position = Position;
			Transform->SetRotation(Rotation);
			Transform->Scale = Scale;
		});
	}
	if (Entity->HasComponent<Volund::Camera>())
	{
		auto& View = Entity->ComponentView<Volund::Camera>();
		this->DrawComponentView(View, "Camera", [this](Volund::Ref<Volund::Component> Component)
		{
			auto Camera = std::dynamic_pointer_cast<Volund::Camera>(Component);

			bool IsActive = Camera->IsActive();
			BoolControl("Active", &IsActive);
			if (IsActive)
			{
				Camera->SetActive();
			}

			FloatControl("FOV", &Camera->FOV);
			FloatControl("FarPlane", &Camera->FarPlane);
			FloatControl("NearPlane", &Camera->NearPlane);
		});
	}
	if (Entity->HasComponent<Volund::MeshRenderer>())
	{
		auto& View = Entity->ComponentView<Volund::MeshRenderer>();
		this->DrawComponentView(View, "MeshRenderer", [this, Scene](Volund::Ref<Volund::Component> Component)
		{
			auto MeshRenderer = std::dynamic_pointer_cast<Volund::MeshRenderer>(Component);

			std::vector<std::string> Materials;
			auto& MaterialView = Scene->Assets.View<Volund::MaterialAsset>();
			for (auto& Material : MaterialView)
			{
				Materials.push_back(Material->GetName());
			}
			std::string SelectedMaterial = TextSelectorControl("Material", MeshRenderer->GetMaterial()->GetName(), Materials);
			if (SelectedMaterial != "")
			{
				if (Scene->Assets.Contains<Volund::MaterialAsset>(SelectedMaterial))
				{
					auto Material = Scene->Assets.Get<Volund::MaterialAsset>(SelectedMaterial);
					MeshRenderer->SetMaterial(Material);
				}
				else
				{
					VOLUND_WARNING("Unable to find MaterialAsset (%s)", SelectedMaterial.c_str());
				}
			}

			std::vector<std::string> Meshes;
			auto& MeshView = Scene->Assets.View<Volund::MeshAsset>();
			for (auto& Mesh : MeshView)
			{
				Meshes.push_back(Mesh->GetName());
			}
			std::string SelectedMesh = TextSelectorControl("Mesh", MeshRenderer->GetMesh()->GetName(), Meshes);
			if (SelectedMesh != "")
			{
				if (Scene->Assets.Contains<Volund::MeshAsset>(SelectedMesh))
				{
					auto Mesh = Scene->Assets.Get<Volund::MeshAsset>(SelectedMesh);
					MeshRenderer->SetMesh(Mesh);
				}
				else
				{
					VOLUND_WARNING("Unable to find MeshAsset (%s)", SelectedMesh.c_str());
				}
			}
		});
	}		
	if (Entity->HasComponent<Volund::PointLight>())
	{
		auto& View = Entity->ComponentView<Volund::PointLight>();
		this->DrawComponentView(View, "PointLight", [this](Volund::Ref<Volund::Component> Component)
		{
			auto PointLight = std::dynamic_pointer_cast<Volund::PointLight>(Component);

			ImGui::ColorPicker3("##Color", glm::value_ptr(PointLight->Color), ImGuiColorEditFlags_Float);
		});
	}
}

void SceneWidget::DrawComponentView(const std::vector<Volund::Ref<Volund::Component>>& ComponentView, std::string_view Name, std::function<void(Volund::Ref<Volund::Component>)> DrawFunction)
{
	for (auto& Component : ComponentView)
	{
		if (ImGui::TreeNodeEx((void*)Component.get(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed, Name.data()))
		{
			DrawFunction(Component);
			ImGui::TreePop();
		}
	}
}

SceneWidget::SceneWidget(Volund::Layer* Parent)
{
	this->_Parent = Parent;
}
