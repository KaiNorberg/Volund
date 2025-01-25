#include "Inspector.hpp"

#include "Editor.hpp"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

void Inspector::OnProcedure(const VL::Event& e)
{
	switch (e.type)
	{
	case VOLUND_EVENT_RENDER:
	{
		auto scene = this->m_context->state->SceneRef();
		auto selectedEntity = this->m_context->selectedEntity;

		if (!scene->IsRegistered(selectedEntity))
		{
			ImGui::Text("No valid entity selected!");
			return;
		}

		//IMPORTANT: Remember to update the code below whenever a new component is implemented.

		this->ImGuiComponent<VL::Tag>("Tag", selectedEntity, [this, selectedEntity, scene](int i)
		{
			auto tag = scene->GetComponent<VL::Tag>(selectedEntity, i);

			ImGuiString("Tag", tag->string);
		});

		this->ImGuiComponent<VL::Transform>("Transform", selectedEntity, [this, selectedEntity, scene](int i)
		{
			auto transform = scene->GetComponent<VL::Transform>(selectedEntity, i);

			VL::Vec3 position = transform->pos;
			VL::Vec3 rotation = transform->GetRotation();
			VL::Vec3 scale = transform->scale;

			ImGuiVec3("Position", position, 0.1f, 0.0f);
			ImGuiVec3("Rotation", rotation, 0.1f, 0.0f);
			ImGuiVec3("Scale", scale, 0.1f, 1.0f);

			transform->pos = position;
			transform->SetRotation(rotation);
			transform->scale = scale;
		});

		this->ImGuiComponent<VL::MeshRenderer>("MeshRenderer", selectedEntity, [this, selectedEntity, scene](int i)
		{
			auto meshRenderer = scene->GetComponent<VL::MeshRenderer>(selectedEntity, i);

			std::shared_ptr<VL::Material> newMaterial = ImGuiAssetSelector("Material", meshRenderer->GetMaterial(), this->m_context->state);
			if (newMaterial != nullptr)
			{
				meshRenderer->SetMaterial(newMaterial);
			}

			std::shared_ptr<VL::Mesh> newMesh = ImGuiAssetSelector("Mesh", meshRenderer->GetMesh(), this->m_context->state);
			if (newMesh != nullptr)
			{
				meshRenderer->SetMesh(newMesh);
			}
		});

		this->ImGuiComponent<VL::Camera>("Camera", selectedEntity, [this, selectedEntity, scene](int i)
		{
			auto camera = scene->GetComponent<VL::Camera>(selectedEntity, i);

			//TODO: Add targetbuffer

			ImGuiFloat("FOV", camera->fov);
			ImGuiFloat("FarPlane", camera->farPlane);
			ImGuiFloat("NearPlane", camera->nearPlane);
		});

		this->ImGuiComponent<VL::CameraMovement>("CameraMovement", selectedEntity, [this, selectedEntity, scene](int i)
		{
			auto cameraMovement = scene->GetComponent<VL::CameraMovement>(selectedEntity, i);

			ImGuiFloat("Speed", cameraMovement->speed);
			ImGuiFloat("Sensitivity", cameraMovement->sensitivity);
		});

		this->ImGuiComponent<VL::PointLight>("PointLight", selectedEntity, [this, selectedEntity, scene](int i)
		{
			auto pointLight = scene->GetComponent<VL::PointLight>(selectedEntity, i);

			std::string label = "##Color" + std::to_string((uint64_t)pointLight.get());
			ImGui::ColorPicker3(label.c_str(), &pointLight->color.x, ImGuiColorEditFlags_Float);

			ImGuiFloat("Brightness", pointLight->brightness);
		});

		this->ImGuiComponent<VL::SoundSource>("SoundSource", selectedEntity, [this, selectedEntity, scene](int i)
		{
			/*auto soundSource = scene->GetComponent<VL::SoundSource>(selectedEntity, i);

			//Todo: Add variables
			std::string audiobufferPath = scene->FetchFilepath<VL::AudioBuffer>(soundSource->GetBuffer());
			if (ImGuiFile("AudioBuffer", audiobufferPath))
			{
				soundSource->SetBuffer(scene->FetchAsset<VL::AudioBuffer>(audiobufferPath));
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
			}*/
		});

		this->ImGuiComponent<VL::SoundListener>("SoundListener", selectedEntity, [this, selectedEntity, scene](int i)
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
				scene->AddComponent<VL::Tag>(selectedEntity);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Transform"))
			{
				scene->AddComponent<VL::Transform>(selectedEntity);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Camera"))
			{
				scene->AddComponent<VL::Camera>(selectedEntity);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("MeshRenderer"))
			{
				scene->AddComponent<VL::MeshRenderer>(selectedEntity);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("PointLight"))
			{
				scene->AddComponent<VL::PointLight>(selectedEntity);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("CameraMovement"))
			{
				scene->AddComponent<VL::CameraMovement>(selectedEntity);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("SoundSource"))
			{
				scene->AddComponent<VL::SoundSource>(selectedEntity);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("SoundListener"))
			{
				scene->AddComponent<VL::SoundListener>(selectedEntity);
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
