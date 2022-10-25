#include "PCH/PCH.h"

#include "InspectorWidget.h"

#include "Editor/Editor.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

const char* InspectorWidget::GetName()
{
	return "InspectorWidget";
}

void InspectorWidget::Draw(VL::TimeStep TS)
{
	auto Scene = this->_Editor->GetScene();

	if (ImGui::Begin("Inspector", &this->_IsActive))
	{
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

	}

	ImGui::End();
}

void InspectorWidget::DrawComponents()
{
	auto Scene = this->_Editor->GetScene();

	if (Scene->HasComponent<VL::Tag>(_SelectedEntity))
	{
		auto& View = Scene->View<VL::Tag>(_SelectedEntity);
		this->DrawComponentView(View, "Transform", [this](VL::Ref<VL::Component> Component)
		{
			auto Tag = std::dynamic_pointer_cast<VL::Tag>(Component);

			std::string NewTag = TextControl("Tag", Tag->String);
			if (NewTag != "")
			{
				Tag->String = NewTag;
			}
		});
	}
	if (Scene->HasComponent<VL::Transform>(_SelectedEntity))
	{
		auto& View = Scene->View<VL::Transform>(_SelectedEntity);
		this->DrawComponentView(View, "Transform", [this](VL::Ref<VL::Component> Component)
		{
			auto Transform = std::dynamic_pointer_cast<VL::Transform>(Component);
			VL::Vec3 Position = Transform->Position;
			VL::Vec3 Rotation = Transform->GetRotation();
			VL::Vec3 Scale = Transform->Scale;

			Vec3Control("Position", &Position, 0.1f, 0.0f);
			Vec3Control("Rotation", &Rotation, 0.1f, 0.0f);
			Vec3Control("Scale", &Scale, 0.1f, 1.0f);

			Transform->Position = Position;
			Transform->SetRotation(Rotation);
			Transform->Scale = Scale;
		});
	}
	if (Scene->HasComponent<VL::Camera>(_SelectedEntity))
	{
		auto& View = Scene->View<VL::Camera>(_SelectedEntity);
		this->DrawComponentView(View, "Camera", [this](VL::Ref<VL::Component> Component)
		{
			auto Camera = std::dynamic_pointer_cast<VL::Camera>(Component);

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
	if (Scene->HasComponent<VL::MeshRenderer>(_SelectedEntity))
	{
		auto& View = Scene->View<VL::MeshRenderer>(_SelectedEntity);
		this->DrawComponentView(View, "MeshRenderer", [this, Scene](VL::Ref<VL::Component> Component)
		{
			auto MeshRenderer = std::dynamic_pointer_cast<VL::MeshRenderer>(Component);
			auto Window = this->_Editor->GetWindow();

			std::string DefaultMaterial = "No Material Selected!";
			if (MeshRenderer->GetMaterial() != nullptr)
			{
				DefaultMaterial = MeshRenderer->GetMaterial()->GetFilepath();
			}
			auto SelectedMaterial = FileSelectorControl("Material", DefaultMaterial, "Volund Material (*.vmaterial)\0*.vmaterial\0", Window);
			if (SelectedMaterial != "")
			{
				MeshRenderer->SetMaterial(VL::Material::Create(SelectedMaterial));
			}

			std::string DefaultMesh = "No Mesh Selected!";
			if (MeshRenderer->GetMesh() != nullptr)
			{
				DefaultMesh = MeshRenderer->GetMesh()->GetFilepath();
			}
			auto SelectedMesh = FileSelectorControl("Mesh", DefaultMesh, "Volund Mesh (*.obj)\0*.obj\0", Window);
			if (SelectedMesh != "")
			{
				MeshRenderer->SetMesh(VL::Mesh::Create(SelectedMesh));
			}
		});
	}
	if (Scene->HasComponent<VL::PointLight>(_SelectedEntity))
	{
		auto& View = Scene->View<VL::PointLight>(_SelectedEntity);
		this->DrawComponentView(View, "PointLight", [this](VL::Ref<VL::Component> Component)
		{
			auto PointLight = std::dynamic_pointer_cast<VL::PointLight>(Component);

			ImGui::ColorPicker3("##Color", glm::value_ptr(PointLight->Color), ImGuiColorEditFlags_Float);

			FloatControl("Brightness", &PointLight->Brightness);
		});
	}
	if (Scene->HasComponent<VL::CameraMovement>(_SelectedEntity))
	{
		auto& View = Scene->View<VL::CameraMovement>(_SelectedEntity);
		this->DrawComponentView(View, "CameraMovement", [this](VL::Ref<VL::Component> Component)
		{
			auto CameraMovement = std::dynamic_pointer_cast<VL::CameraMovement>(Component);

			FloatControl("Speed", &CameraMovement->Speed);
			FloatControl("Sensitivity", &CameraMovement->Sensitivity);
		});
	}
}

void InspectorWidget::DrawAddComponents()
{
	auto Scene = this->_Editor->GetScene();

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
			Scene->CreateComponent<VL::Tag>(_SelectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Transform"))
		{
			Scene->CreateComponent<VL::Transform>(_SelectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Camera"))
		{
			Scene->CreateComponent<VL::Camera>(_SelectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("MeshRenderer"))
		{
			Scene->CreateComponent<VL::MeshRenderer>(_SelectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("PointLight"))
		{
			Scene->CreateComponent<VL::PointLight>(_SelectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("CameraMovement"))
		{
			Scene->CreateComponent<VL::CameraMovement>(_SelectedEntity);
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

void InspectorWidget::DrawComponentView(const std::vector<VL::Ref<VL::Component>>& ComponentView, std::string_view Name, std::function<void(VL::Ref<VL::Component>)> DrawFunction)
{
	auto Scene = this->_Editor->GetScene();

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