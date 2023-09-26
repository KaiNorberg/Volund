#include "PCH/PCH.h"

#include "InspectorWindow.h"

#include "Editor/Editor.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

void InspectorWindow::OnProcedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VOLUND_EVENT_TYPE_RENDER:
	{
		auto scene = this->m_Context->GetScene();
		auto selectedEntity = this->m_Context->SelectedEntity;

		if (scene == nullptr || !scene->IsEntityRegistered(selectedEntity))
		{
			ImGui::Text("No valid entity selected!");
			return;
		}

		auto assetManager = this->m_Context->GetAssetmanager();

		//IMPORTANT: Remember to update the code below whenever a new component is implemented.

		this->ImGuiComponent<VL::Tag>("Tag", selectedEntity, [this, selectedEntity, scene](int i)
		{
			auto tag = scene->GetComponent<VL::Tag>(selectedEntity, i);

			ImGuiString("Tag", tag->String);
		});

		this->ImGuiComponent<VL::Transform>("Transform", selectedEntity, [this, selectedEntity, scene](int i)
		{
			auto transform = scene->GetComponent<VL::Transform>(selectedEntity, i);

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

		this->ImGuiComponent<VL::MeshRenderer>("MeshRenderer", selectedEntity, [this, selectedEntity, scene, assetManager](int i)
		{
			auto meshRenderer = scene->GetComponent<VL::MeshRenderer>(selectedEntity, i);
			auto window = this->m_Context->GetWindow();

			std::string materialPath = assetManager->FetchFilepath<VL::Material>(meshRenderer->GetMaterial());
			if (ImGuiFile("Material", materialPath))
			{
				meshRenderer->SetMaterial(assetManager->Fetch<VL::Material>(materialPath));
			}

			std::string meshPath = assetManager->FetchFilepath<VL::Mesh>(meshRenderer->GetMesh());
			if (ImGuiFile("Mesh", meshPath))
			{
				meshRenderer->SetMesh(assetManager->Fetch<VL::Mesh>(meshPath));
			}
		});

		this->ImGuiComponent<VL::Camera>("Camera", selectedEntity, [this, selectedEntity, scene](int i)
		{
			auto camera = scene->GetComponent<VL::Camera>(selectedEntity, i);

			//TODO: Add targetbuffer

			ImGuiFloat("FOV", camera->FOV);
			ImGuiFloat("FarPlane", camera->FarPlane);
			ImGuiFloat("NearPlane", camera->NearPlane);
		});

		this->ImGuiComponent<VL::CameraMovement>("CameraMovement", selectedEntity, [this, selectedEntity, scene](int i)
		{
			auto cameraMovement = scene->GetComponent<VL::CameraMovement>(selectedEntity, i);

			ImGuiFloat("Speed", cameraMovement->Speed);
			ImGuiFloat("Sensitivity", cameraMovement->Sensitivity);
		});

		this->ImGuiComponent<VL::PointLight>("PointLight", selectedEntity, [this, selectedEntity, scene](int i)
		{
			auto pointLight = scene->GetComponent<VL::PointLight>(selectedEntity, i);

			std::string label = "##Color" + std::to_string((uint64_t)pointLight.get());
			ImGui::ColorPicker3(label.c_str(), glm::value_ptr(pointLight->Color), ImGuiColorEditFlags_Float);

			ImGuiFloat("Brightness", pointLight->Brightness);
		});

		this->ImGuiComponent<VL::SoundSource>("SoundSource", selectedEntity, [this, selectedEntity, scene, assetManager](int i)
		{
			auto soundSource = scene->GetComponent<VL::SoundSource>(selectedEntity, i);
			auto window = this->m_Context->GetWindow();

			//Todo: Add variables
			std::string audiobufferPath = assetManager->FetchFilepath<VL::AudioBuffer>(soundSource->GetBuffer());
			if (ImGuiFile("AudioBuffer", audiobufferPath))
			{
				soundSource->SetBuffer(assetManager->Fetch<VL::AudioBuffer>(audiobufferPath));
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

		this->ImGuiComponent<VL::SoundListener>("SoundListener", selectedEntity, [this, selectedEntity, scene](int i)
		{
		});

		this->ImGuiComponent<VL::ScriptComponent>("Script", selectedEntity, [this, selectedEntity, scene, assetManager](int i)
		{
			auto scriptComponent = scene->GetComponent<VL::ScriptComponent>(selectedEntity, i);
			VL::Ref<VL::Script> script = scriptComponent->GetScript();

			std::string scriptPath;
			if (script != nullptr)
			{
				scriptPath = script->GetFilepath();
			}
			if (ImGuiFile("Script", scriptPath))
			{
				auto script = assetManager->LoadScript(scriptPath);
				scriptComponent->SetScript(script);
			}

			if (script != nullptr)
			{
				for (const std::string& identifier : script->GetPublicVariables())
				{
					if (script->IsVariable<int>(identifier))
					{
						auto rawValue = script->GetVariable<int>(identifier);
						if (ImGuiInt(identifier, rawValue))
						{
							script->SetVariable(identifier, rawValue);
						}
					}
					else if (script->IsVariable<double>(identifier))
					{
						auto rawValue = script->GetVariable<double>(identifier);
						if (ImGuiDouble(identifier, rawValue))
						{
							script->SetVariable(identifier, rawValue);
						}
					}
					else if (script->IsVariable<std::string>(identifier))
					{
						auto rawValue = script->GetVariable<std::string>(identifier);
						if (ImGuiString(identifier, rawValue))
						{
							script->SetVariable(identifier, rawValue);
						}
					}
				}
			}
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
			if (ImGui::MenuItem("Script"))
			{
				scene->CreateComponent<VL::ScriptComponent>(selectedEntity);
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}
	break;
	}
}

InspectorWindow::InspectorWindow(VL::Ref<EditorContext> context)
{
	this->SetName("Inspector");

	this->m_Context = context;
}