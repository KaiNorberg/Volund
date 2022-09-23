#include "PCH/PCH.h"
#include "EntitiesWidget.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

#include "Editor/EditorLayer/EditorLayer.h"

const char* EntitiesWidget::GetName()
{
	return "Entities";
}

void EntitiesWidget::OnUpdate(TimeStep TS)
{
	auto Scene = this->_Parent->GetLayer<EditorLayer>()->GetProject()->GetScene();

	if (ImGui::Begin("Entities", &this->_IsActive))
	{
		if (Scene != nullptr)
		{
			this->DrawEntityTab(Scene);

			if (Scene->HasEntity(this->_SelectedEntity))
			{
				this->DrawInspector(Scene->GetEntity(this->_SelectedEntity), Scene);
			}
		}
		else
		{
			ImGui::Text("No Scene Loaded!");
		}
	}

	ImGui::End();
}

void EntitiesWidget::DrawEntityTab(Volund::Ref<Volund::Scene> Scene)
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
					if (!this->DrawEntityNode(Scene, Entity))
					{
						break;
					}
				}
			}
		}

		ImGui::EndListBox();
	}
}

bool EntitiesWidget::DrawEntityNode(Volund::Ref<Volund::Scene> Scene, Volund::Ref<Volund::Entity> Entity)
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

	bool EntityAlive = true;
	if (ImGui::BeginPopupContextItem())
	{
		if (ImGui::MenuItem("Delete"))
		{
			Scene->DeleteEntity(Entity->GetName());
			EntityAlive = false;
		}

		ImGui::EndPopup();
	}

	ImGui::PopID();

	return EntityAlive;
}

void EntitiesWidget::DrawInspector(Volund::Ref<Volund::Entity> Entity, Volund::Ref<Volund::Scene> Scene)
{
	std::string EntityName = Entity->GetName();
	ImGui::InputText("##EntityName", &EntityName);
	if (EntityName != Entity->GetName())
	{
		_SelectedEntity = EntityName;
		Entity->SetName(EntityName);
	}

	ImGui::SameLine();

	if (ImGui::Button("Add Component"))
	{
		ImGui::OpenPopup("Add Component");
	}

	if (ImGui::BeginPopup("Add Component"))
	{
		if (ImGui::MenuItem("Transform"))
		{
			Entity->CreateComponent<Transform>();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Camera"))
		{
			Entity->CreateComponent<Camera>();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("MeshRenderer"))
		{
			Entity->CreateComponent<MeshRenderer>();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("PointLight"))
		{
			Entity->CreateComponent<PointLight>();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("CameraMovement"))
		{
			Entity->CreateComponent<CameraMovement>();
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
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

			std::string DefaultMaterial = "";
			if (MeshRenderer->GetMaterial() != nullptr)
			{
				DefaultMaterial = MeshRenderer->GetMaterial()->GetFilepath();
			}
			auto SelectedMaterial = FileSelectorControl("Material", DefaultMaterial, ".vmaterial");
			if (SelectedMaterial != "")
			{
				MeshRenderer->SetMaterial(AssetLibrary::Load<Material>(SelectedMaterial));
			}

			std::string DefaultMesh = "";
			if (MeshRenderer->GetMesh() != nullptr)
			{
				DefaultMesh = MeshRenderer->GetMesh()->GetFilepath();
			}
			auto SelectedMesh = FileSelectorControl("Mesh", DefaultMesh, ".obj");
			if (SelectedMesh != "")
			{
				MeshRenderer->SetMesh(AssetLibrary::Load<Mesh>(SelectedMesh));
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
	if (Entity->HasComponent<Volund::CameraMovement>())
	{
		auto& View = Entity->ComponentView<Volund::CameraMovement>();
		this->DrawComponentView(View, "CameraMovement", [this](Volund::Ref<Volund::Component> Component)
		{
			auto CameraMovement = std::dynamic_pointer_cast<Volund::CameraMovement>(Component);

			FloatControl("Speed", &CameraMovement->Speed);
			FloatControl("Sensitivity", &CameraMovement->Sensitivity);
		});
	}
}

void EntitiesWidget::DrawComponentView(const std::vector<Volund::Ref<Volund::Component>>& ComponentView, std::string_view Name, std::function<void(Volund::Ref<Volund::Component>)> DrawFunction)
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

EntitiesWidget::EntitiesWidget(Volund::Layer* Parent)
{
	this->_Parent = Parent;
}
