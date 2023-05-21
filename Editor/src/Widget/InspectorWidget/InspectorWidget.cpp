#include "PCH/PCH.h"

#include "InspectorWidget.h"

#include "Editor/Editor.h"
#include "Editor/EditorContext/EditorContext.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

const char* InspectorWidget::GetName()
{
	return "Inspector";
}

void InspectorWidget::Procedure(const VL::Event& e)
{	
	switch (e.Type)
	{
	case VL::EventType::Render:
	{
		if (ImGui::Begin(this->GetName(), &this->IsActive))
		{
			auto scene = this->m_Context->GetScene();
			auto selectedEntity = this->m_Context->SelectedEntity;

			if (scene != nullptr && scene->IsEntityRegistered(selectedEntity))
			{
				ImGui::Separator();

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
	break;
	case VL::EventType::Update:
	{
	}
	break;
	}
}


void InspectorWidget::DrawComponents()
{
	auto scene = this->m_Context->GetScene();
	auto selectedEntity = this->m_Context->SelectedEntity;

	//IMPORTANT: Remember to update the code below whenever a new component is implemented.

	this->DrawComponent<VL::Tag>("Tag", selectedEntity, [this, selectedEntity, scene](int i)
	{
		auto tag = scene->GetComponent<VL::Tag>(selectedEntity, i);

		std::string newTag = this->TextControl("Tag", tag->String);
		if (newTag != "")
		{
			tag->String = newTag;
		}
	});

	this->DrawComponent<VL::Transform>("Transform", selectedEntity, [this, selectedEntity, scene](int i)
	{
		auto transform = scene->GetComponent<VL::Transform>(selectedEntity, i);

		VL::Vec3 position = transform->Position;
		VL::Vec3 rotation = transform->GetRotation();
		VL::Vec3 scale = transform->Scale;

		this->Vec3Control("Position", &position, 0.1f, 0.0f);
		this->Vec3Control("Rotation", &rotation, 0.1f, 0.0f);
		this->Vec3Control("Scale", &scale, 0.1f, 1.0f);

		transform->Position = position;
		transform->SetRotation(rotation);
		transform->Scale = scale;
	});

	this->DrawComponent<VL::MeshRenderer>("MeshRenderer", selectedEntity, [this, selectedEntity, scene](int i)
	{
		auto meshRenderer = scene->GetComponent<VL::MeshRenderer>(selectedEntity, i);
		auto window = this->m_Context->GetWindow();

		std::string defaultMaterial = scene->FetchAssetFilepath<VL::Material>(meshRenderer->GetMaterial());
		auto selectedMaterial = FileSelectorControl("Material", defaultMaterial, window);
		if (selectedMaterial != "")
		{
			meshRenderer->SetMaterial(scene->FetchAsset<VL::Material>(selectedMaterial));
		}

		std::string defaultMesh = scene->FetchAssetFilepath<VL::Mesh>(meshRenderer->GetMesh());
		auto selectedMesh = FileSelectorControl("Mesh", defaultMesh, window);
		if (selectedMesh != "")
		{
			meshRenderer->SetMesh(scene->FetchAsset<VL::Mesh>(selectedMesh));
		}
	});

	this->DrawComponent<VL::Camera>("Camera", selectedEntity, [this, selectedEntity, scene](int i)
	{
		auto camera = scene->GetComponent<VL::Camera>(selectedEntity, i);

		//TODO: Add targetbuffer

		this->FloatControl("FOV", &camera->FOV);
		this->FloatControl("FarPlane", &camera->FarPlane);
		this->FloatControl("NearPlane", &camera->NearPlane);
	});

	this->DrawComponent<VL::CameraMovement>("CameraMovement", selectedEntity, [this, selectedEntity, scene](int i)
	{
		auto cameraMovement = scene->GetComponent<VL::CameraMovement>(selectedEntity, i);

		FloatControl("Speed", &cameraMovement->Speed);
		FloatControl("Sensitivity", &cameraMovement->Sensitivity);
	});

	this->DrawComponent<VL::PointLight>("PointLight", selectedEntity, [this, selectedEntity, scene](int i)
	{
		auto pointLight = scene->GetComponent<VL::PointLight>(selectedEntity, i);

		std::string label = "##Color" + std::to_string((int)pointLight.get());
		ImGui::ColorPicker3(label.c_str(), glm::value_ptr(pointLight->Color), ImGuiColorEditFlags_Float);

		FloatControl("Brightness", &pointLight->Brightness);
	});

	this->DrawComponent<VL::SoundSource>("SoundSource", selectedEntity, [this, selectedEntity, scene](int i)
	{
		auto soundSource = scene->GetComponent<VL::SoundSource>(selectedEntity, i);
		auto window = this->m_Context->GetWindow();

		//Todo: Add variables
		std::string defaultSound = scene->FetchAssetFilepath<VL::AudioBuffer>(soundSource->GetBuffer());
		auto selectedSound = FileSelectorControl("AudioBuffer", defaultSound, window);
		if (selectedSound != "")
		{
			soundSource->SetBuffer(scene->FetchAsset<VL::AudioBuffer>(selectedSound));
		}

		BoolControl("AutoPlay", &soundSource->AutoPlay);

		bool oldLooping = soundSource->GetLooping();
		bool newLooping = oldLooping;
		BoolControl("Looping", &newLooping);
		if (oldLooping != newLooping)
		{
			soundSource->SetLooping(newLooping);
		}

		float oldPitch = soundSource->GetPitch();
		float newPitch = oldPitch;
		FloatControl("Pitch", &newPitch);
		if (oldPitch != newPitch)
		{
			soundSource->SetPitch(newPitch);
		}

		float oldGain = soundSource->GetGain();
		float newGain = oldGain;
		FloatControl("Gain", &newGain);
		if (oldLooping != newLooping)
		{
			soundSource->SetGain(newGain);
		}
	});

	this->DrawComponent<VL::SoundListener>("SoundListener", selectedEntity, [this, selectedEntity, scene](int i)
	{
	});
}

void InspectorWidget::DrawAddComponents()
{
	auto scene = this->m_Context->GetScene();
	auto selectedEntity = this->m_Context->SelectedEntity;

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
			scene->CreateComponent<VL::Tag>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Transform"))
		{
			scene->CreateComponent<VL::Transform>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Camera"))
		{
			scene->CreateComponent<VL::Camera>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("MeshRenderer"))
		{
			scene->CreateComponent<VL::MeshRenderer>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("PointLight"))
		{
			scene->CreateComponent<VL::PointLight>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("CameraMovement"))
		{
			scene->CreateComponent<VL::CameraMovement>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("SoundSource"))
		{
			scene->CreateComponent<VL::SoundSource>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("SoundListener"))
		{
			scene->CreateComponent<VL::SoundListener>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

InspectorWidget::InspectorWidget(VL::Ref<EditorContext> context)
{
	this->m_Context = context;
}
