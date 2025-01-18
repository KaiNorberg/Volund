#include "Inspector.h"

#include "Editor.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

void Inspector::OnProcedure(const VL::Event& e)
{
	switch (e.type)
	{
	case VOLUND_EVENT_RENDER:
	{
		auto gameState = this->m_context->GameState;
		auto selectedEntity = this->m_context->SelectedEntity;

		if (!gameState->IsAllocated(selectedEntity))
		{
			ImGui::Text("No valid entity selected!");
			return;
		}

		//IMPORTANT: Remember to update the code below whenever a new component is implemented.

		this->ImGuiComponent<VL::Tag>("Tag", selectedEntity, [this, selectedEntity, gameState](int i)
		{
			auto tag = gameState->GetComponent<VL::Tag>(selectedEntity, i);

			ImGuiString("Tag", tag->String);
		});

		this->ImGuiComponent<VL::Transform>("Transform", selectedEntity, [this, selectedEntity, gameState](int i)
		{
			auto transform = gameState->GetComponent<VL::Transform>(selectedEntity, i);

			VL::Vec3 position = transform->Position;
			VL::Vec3 rotation = transform->GetRotation();
			VL::Vec3 scale = transform->Scale;

			ImGuiVec3("Position", position, 0.1f, 0.0f);
			ImGuiVec3("Rotation", rotation, 0.1f, 0.0f);
			ImGuiVec3("Scale", scale, 0.1f, 1.0f);

			transform->Position = position;
			transform->SetRotation(rotation);
			transform->Scale = scale;
		});

		this->ImGuiComponent<VL::MeshRenderer>("MeshRenderer", selectedEntity, [this, selectedEntity, gameState](int i)
		{
			auto meshRenderer = gameState->GetComponent<VL::MeshRenderer>(selectedEntity, i);

			std::string materialPath = gameState->FetchFilepath<VL::Material>(meshRenderer->GetMaterial());
			if (ImGuiFile("Material", materialPath))
			{
				meshRenderer->SetMaterial(gameState->FetchAsset<VL::Material>(materialPath));
			}

			std::string meshPath = gameState->FetchFilepath<VL::Mesh>(meshRenderer->GetMesh());
			if (ImGuiFile("Mesh", meshPath))
			{
				meshRenderer->SetMesh(gameState->FetchAsset<VL::Mesh>(meshPath));
			}
		});

		this->ImGuiComponent<VL::Camera>("Camera", selectedEntity, [this, selectedEntity, gameState](int i)
		{
			auto camera = gameState->GetComponent<VL::Camera>(selectedEntity, i);

			//TODO: Add targetbuffer

			ImGuiFloat("FOV", camera->FOV);
			ImGuiFloat("FarPlane", camera->FarPlane);
			ImGuiFloat("NearPlane", camera->NearPlane);
		});

		this->ImGuiComponent<VL::CameraMovement>("CameraMovement", selectedEntity, [this, selectedEntity, gameState](int i)
		{
			auto cameraMovement = gameState->GetComponent<VL::CameraMovement>(selectedEntity, i);

			ImGuiFloat("Speed", cameraMovement->Speed);
			ImGuiFloat("Sensitivity", cameraMovement->Sensitivity);
		});

		this->ImGuiComponent<VL::PointLight>("PointLight", selectedEntity, [this, selectedEntity, gameState](int i)
		{
			auto pointLight = gameState->GetComponent<VL::PointLight>(selectedEntity, i);

			std::string label = "##Color" + std::to_string((uint64_t)pointLight.get());
			ImGui::ColorPicker3(label.c_str(), &pointLight->Color.x, ImGuiColorEditFlags_Float);

			ImGuiFloat("Brightness", pointLight->Brightness);
		});

		this->ImGuiComponent<VL::SoundSource>("SoundSource", selectedEntity, [this, selectedEntity, gameState](int i)
		{
			auto soundSource = gameState->GetComponent<VL::SoundSource>(selectedEntity, i);

			//Todo: Add variables
			std::string audiobufferPath = gameState->FetchFilepath<VL::AudioBuffer>(soundSource->GetBuffer());
			if (ImGuiFile("AudioBuffer", audiobufferPath))
			{
				soundSource->SetBuffer(gameState->FetchAsset<VL::AudioBuffer>(audiobufferPath));
			}

			ImGuiBool("AutoPlay", soundSource->AutoPlay);

			bool oldLooping = soundSource->GetLooping();
			bool newLooping = oldLooping;
			ImGuiBool("Looping", newLooping);
			if (oldLooping != newLooping)
			{
				soundSource->SetLooping(newLooping);
			}

			float oldPitch = soundSource->GetPitch();
			float newPitch = oldPitch;
			ImGuiFloat("Pitch", newPitch);
			if (oldPitch != newPitch)
			{
				soundSource->SetPitch(newPitch);
			}

			float oldGain = soundSource->GetGain();
			float newGain = oldGain;
			ImGuiFloat("Gain", newGain);
			if (oldLooping != newLooping)
			{
				soundSource->SetGain(newGain);
			}
		});

		this->ImGuiComponent<VL::SoundListener>("SoundListener", selectedEntity, [this, selectedEntity, gameState](int i)
		{
		});

		ImGuiAlign("Add Component", 0.5f);
		if (ImGui::Button("Add Component"))
		{
			ImGui::OpenPopup("Add Component");
		}

		if (ImGui::BeginPopup("Add Component"))
		{
			if (ImGui::MenuItem("Tag"))
			{
				gameState->CreateComponent<VL::Tag>(selectedEntity);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Transform"))
			{
				gameState->CreateComponent<VL::Transform>(selectedEntity);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Camera"))
			{
				gameState->CreateComponent<VL::Camera>(selectedEntity);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("MeshRenderer"))
			{
				gameState->CreateComponent<VL::MeshRenderer>(selectedEntity);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("PointLight"))
			{
				gameState->CreateComponent<VL::PointLight>(selectedEntity);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("CameraMovement"))
			{
				gameState->CreateComponent<VL::CameraMovement>(selectedEntity);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("SoundSource"))
			{
				gameState->CreateComponent<VL::SoundSource>(selectedEntity);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("SoundListener"))
			{
				gameState->CreateComponent<VL::SoundListener>(selectedEntity);
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}
	break;
	}
}

Inspector::Inspector(std::shared_ptr<EditorContext> context)
{
	this->SetName("Inspector");

	this->m_context = context;
}
