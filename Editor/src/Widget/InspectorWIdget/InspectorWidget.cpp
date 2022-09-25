#include "PCH/PCH.h"

#include "InspectorWidget.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

#include "Editor/EditorLayer/EditorLayer.h"

const char* InspectorWidget::GetName()
{
	return "InspectorWidget";
}

void InspectorWidget::OnUpdate(Volund::TimeStep TS)
{
	auto Scene = this->_Parent->GetLayer<EditorLayer>()->GetScene();

	ImGui::Begin("Inspector", &this->_IsActive);

	if (Scene != nullptr && Scene->HasEntity(_SelectedEntity))
	{
		this->DrawComponents();

		ImGui::Separator();

		this->DrawAddComponents();
	}
	else
	{
		ImGui::Text("No Entity Selected!");
	}

	ImGui::End();
}

void InspectorWidget::DrawComponents()
{
	auto Scene = this->_Parent->GetLayer<EditorLayer>()->GetScene();

	if (Scene->HasComponent<Volund::Tag>(_SelectedEntity))
	{
		auto& View = Scene->View<Volund::Tag>(_SelectedEntity);
		this->DrawComponentView(View, "Transform", [this](Volund::Ref<Volund::Component> Component)
		{
			auto Tag = std::dynamic_pointer_cast<Volund::Tag>(Component);

			std::string NewTag = TextControl("Tag", Tag->String);
			if (NewTag != "")
			{
				Tag->String = NewTag;
			}
		});
	}
	if (Scene->HasComponent<Volund::Transform>(_SelectedEntity))
	{
		auto& View = Scene->View<Volund::Transform>(_SelectedEntity);
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
	if (Scene->HasComponent<Volund::Camera>(_SelectedEntity))
	{
		auto& View = Scene->View<Volund::Camera>(_SelectedEntity);
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
	if (Scene->HasComponent<Volund::MeshRenderer>(_SelectedEntity))
	{
		auto& View = Scene->View<Volund::MeshRenderer>(_SelectedEntity);
		this->DrawComponentView(View, "MeshRenderer", [this, Scene](Volund::Ref<Volund::Component> Component)
		{
			auto MeshRenderer = std::dynamic_pointer_cast<Volund::MeshRenderer>(Component);
			auto Window = this->_Parent->GetLayer<EditorLayer>()->GetWindow();

			std::string DefaultMaterial = "No Material Selected!";
			if (MeshRenderer->GetMaterial() != nullptr)
			{
				DefaultMaterial = MeshRenderer->GetMaterial()->GetFilepath();
			}
			auto SelectedMaterial = FileSelectorControl("Material", DefaultMaterial, "Volund Material (*.vmaterial)\0*.vmaterial\0", Window);
			if (SelectedMaterial != "")
			{
				MeshRenderer->SetMaterial(Material::Create(SelectedMaterial));
			}

			std::string DefaultMesh = "No Mesh Selected!";
			if (MeshRenderer->GetMesh() != nullptr)
			{
				DefaultMesh = MeshRenderer->GetMesh()->GetFilepath();
			}
			auto SelectedMesh = FileSelectorControl("Mesh", DefaultMesh, "Volund Mesh (*.obj)\0*.obj\0", Window);
			if (SelectedMesh != "")
			{
				MeshRenderer->SetMesh(Mesh::Create(SelectedMesh));
			}
		});
	}
	if (Scene->HasComponent<Volund::PointLight>(_SelectedEntity))
	{
		auto& View = Scene->View<Volund::PointLight>(_SelectedEntity);
		this->DrawComponentView(View, "PointLight", [this](Volund::Ref<Volund::Component> Component)
		{
			auto PointLight = std::dynamic_pointer_cast<Volund::PointLight>(Component);

			ImGui::ColorPicker3("##Color", glm::value_ptr(PointLight->Color), ImGuiColorEditFlags_Float);
		});
	}
	if (Scene->HasComponent<Volund::CameraMovement>(_SelectedEntity))
	{
		auto& View = Scene->View<Volund::CameraMovement>(_SelectedEntity);
		this->DrawComponentView(View, "CameraMovement", [this](Volund::Ref<Volund::Component> Component)
		{
			auto CameraMovement = std::dynamic_pointer_cast<Volund::CameraMovement>(Component);

			FloatControl("Speed", &CameraMovement->Speed);
			FloatControl("Sensitivity", &CameraMovement->Sensitivity);
		});
	}
}

void InspectorWidget::DrawAddComponents()
{
	auto Scene = this->_Parent->GetLayer<EditorLayer>()->GetScene();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

	Align(ImGui::CalcTextSize("Add Component").x, 0.5f);
	if (ImGui::Button("Add Component"))
	{
		ImGui::OpenPopup("Add Component");
	}

	if (ImGui::BeginPopup("Add Component"))
	{
		if (ImGui::MenuItem("Tag"))
		{
			Scene->CreateComponent<Tag>(_SelectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Transform"))
		{
			Scene->CreateComponent<Transform>(_SelectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Camera"))
		{
			Scene->CreateComponent<Camera>(_SelectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("MeshRenderer"))
		{
			Scene->CreateComponent<MeshRenderer>(_SelectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("PointLight"))
		{
			Scene->CreateComponent<PointLight>(_SelectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("CameraMovement"))
		{
			Scene->CreateComponent<CameraMovement>(_SelectedEntity);
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

void InspectorWidget::DrawComponentView(const std::vector<Volund::Ref<Volund::Component>>& ComponentView, std::string_view Name, std::function<void(Volund::Ref<Volund::Component>)> DrawFunction)
{
	auto Scene = this->_Parent->GetLayer<EditorLayer>()->GetScene();

	for (auto& Component : ComponentView)
	{
		bool Open = ImGui::TreeNodeEx((void*)Component.get(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_ClipLabelForTrailingButton, Name.data());
		
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete"))
			{
				Scene->DeleteComponent(Component.get());
			}

			ImGui::EndPopup();
		}

		if (Open)
		{
			DrawFunction(Component);
			ImGui::TreePop();
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
		}
	}
}

InspectorWidget::InspectorWidget(Volund::Layer* Parent, bool Active)
{
	this->_Parent = Parent;
	this->_IsActive = Active;
}