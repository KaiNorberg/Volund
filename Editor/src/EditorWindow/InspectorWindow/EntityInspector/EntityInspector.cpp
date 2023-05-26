#include "PCH/PCH.h"
#include "EntityInspector.h"

#include "Utils/Utils.h"

void EntityInspector::Procedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VL::EventType::Render:
	{
		auto scene = this->m_Context->GetScene();
		auto selectedEntity = this->m_Context->SelectedEntity;

		if (scene == nullptr || !scene->IsEntityRegistered(selectedEntity))
		{
			break;
		}

		//IMPORTANT: Remember to update the code below whenever a new component is implemented.

		this->DrawComponent<VL::Tag>("Tag", selectedEntity, [this, selectedEntity, scene](int i)
		{
			auto tag = scene->GetComponent<VL::Tag>(selectedEntity, i);

			std::string newTag = Utils::ImGuiString("Tag", tag->String);
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

			Utils::ImGuiVec3("Position", &position, 0.1f, 0.0f);
			Utils::ImGuiVec3("Rotation", &rotation, 0.1f, 0.0f);
			Utils::ImGuiVec3("Scale", &scale, 0.1f, 1.0f);

			transform->Position = position;
			transform->SetRotation(rotation);
			transform->Scale = scale;
		});

		this->DrawComponent<VL::MeshRenderer>("MeshRenderer", selectedEntity, [this, selectedEntity, scene](int i)
		{
			auto meshRenderer = scene->GetComponent<VL::MeshRenderer>(selectedEntity, i);
			auto window = this->m_Context->GetWindow();

			std::string defaultMaterial = scene->FetchAssetFilepath<VL::Material>(meshRenderer->GetMaterial());
			auto selectedMaterial = Utils::ImGuiFileSelector("Material", defaultMaterial, window);
			if (selectedMaterial != "")
			{
				meshRenderer->SetMaterial(scene->FetchAsset<VL::Material>(selectedMaterial));
			}

			std::string defaultMesh = scene->FetchAssetFilepath<VL::Mesh>(meshRenderer->GetMesh());
			auto selectedMesh = Utils::ImGuiFileSelector("Mesh", defaultMesh, window);
			if (selectedMesh != "")
			{
				meshRenderer->SetMesh(scene->FetchAsset<VL::Mesh>(selectedMesh));
			}
		});

		this->DrawComponent<VL::Camera>("Camera", selectedEntity, [this, selectedEntity, scene](int i)
		{
			auto camera = scene->GetComponent<VL::Camera>(selectedEntity, i);

			//TODO: Add targetbuffer

			Utils::ImGuiFloat("FOV", &camera->FOV);
			Utils::ImGuiFloat("FarPlane", &camera->FarPlane);
			Utils::ImGuiFloat("NearPlane", &camera->NearPlane);
		});

		this->DrawComponent<VL::CameraMovement>("CameraMovement", selectedEntity, [this, selectedEntity, scene](int i)
		{
			auto cameraMovement = scene->GetComponent<VL::CameraMovement>(selectedEntity, i);

			Utils::ImGuiFloat("Speed", &cameraMovement->Speed);
			Utils::ImGuiFloat("Sensitivity", &cameraMovement->Sensitivity);
		});

		this->DrawComponent<VL::PointLight>("PointLight", selectedEntity, [this, selectedEntity, scene](int i)
		{
			auto pointLight = scene->GetComponent<VL::PointLight>(selectedEntity, i);

			std::string label = "##Color" + std::to_string((int)pointLight.get());
			ImGui::ColorPicker3(label.c_str(), glm::value_ptr(pointLight->Color), ImGuiColorEditFlags_Float);

			Utils::ImGuiFloat("Brightness", &pointLight->Brightness);
		});

		this->DrawComponent<VL::SoundSource>("SoundSource", selectedEntity, [this, selectedEntity, scene](int i)
		{
			auto soundSource = scene->GetComponent<VL::SoundSource>(selectedEntity, i);
			auto window = this->m_Context->GetWindow();

			//Todo: Add variables
			std::string defaultSound = scene->FetchAssetFilepath<VL::AudioBuffer>(soundSource->GetBuffer());
			auto selectedSound = Utils::ImGuiFileSelector("AudioBuffer", defaultSound, window);
			if (selectedSound != "")
			{
				soundSource->SetBuffer(scene->FetchAsset<VL::AudioBuffer>(selectedSound));
			}

			Utils::ImGuiBool("AutoPlay", &soundSource->AutoPlay);

			bool oldLooping = soundSource->GetLooping();
			bool newLooping = oldLooping;
			Utils::ImGuiBool("Looping", &newLooping);
			if (oldLooping != newLooping)
			{
				soundSource->SetLooping(newLooping);
			}

			float oldPitch = soundSource->GetPitch();
			float newPitch = oldPitch;
			Utils::ImGuiFloat("Pitch", &newPitch);
			if (oldPitch != newPitch)
			{
				soundSource->SetPitch(newPitch);
			}

			float oldGain = soundSource->GetGain();
			float newGain = oldGain;
			Utils::ImGuiFloat("Gain", &newGain);
			if (oldLooping != newLooping)
			{
				soundSource->SetGain(newGain);
			}
		});

		this->DrawComponent<VL::SoundListener>("SoundListener", selectedEntity, [this, selectedEntity, scene](int i)
		{
		});
	}
	break;
	case VL::EventType::Update:
	{
	}
	break;
	}
}

EntityInspector::EntityInspector(const std::string& id, VL::Ref<EditorContext> context)
{
	this->m_Id = id;
	this->m_Context = context;
}